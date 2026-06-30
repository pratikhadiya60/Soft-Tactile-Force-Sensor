#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90393.h>
#include <WiFi.h>
#include <HTTPClient.h>
Adafruit_MLX90393 sensor = Adafruit_MLX90393();

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverUrl = "http://<SERVER_IP>:5000/data";
// Raw values
float x, y, z;

// Hard iron (offset)
float x_offset = 0, y_offset = 0, z_offset = 0;

// Soft iron (scale)
float x_scale = 1, y_scale = 1, z_scale = 1;

// Earth field
float x_earth = 0, y_earth = 0, z_earth = 0;

//for distance calculation   
float R_ref = 60;   
float B_ref = 0;              // will be set after placing magnet
bool magnetCalibrated = false;

// Min/Max for calibration
float x_min = 9999, x_max = -9999;
float y_min = 9999, y_max = -9999;
float z_min = 9999, z_max = -9999;

// for smothning values 

bool calibrated = false;

// ===== FORCE TABLE =====
const int n = 32;

float disp[n] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

float force[n] = { 0, 1.833, 3.5, 5, 6.25, 7.41667, 8.5, 9.5, 10.4167, 11.1667, 12, 12.6667, 13.25, 13.75, 14.25, 14.75, 15, 15.3333, 15.5, 15.5833, 15.5833, 15.5833, 15.5, 15.33, 15, 14.33, 13.5833, 13, 12.5, 12.25, 12.0833, 12 };

// ===== INTERPOLATION FUNCTION =====
float getForce(float x) {

  if (x <= disp[0]) return force[0];
    if (x >= disp[n-1]) return force[n-1];

  for (int i = 0; i < n-1; i++) {
    if (x >= disp[i] && x <= disp[i+1]) {

      float x1 = disp[i];
      float x2 = disp[i+1];
      float y1 = force[i];
      float y2 = force[i+1];

      return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    }
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();


  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  if (!sensor.begin_I2C()) {
    Serial.println("Sensor not found!");
    while (1);
  }

  Serial.println("=== FULL CALIBRATION MODE ===");
  Serial.println("Rotate sensor in all directions...");
  Serial.println("Press 'f' when done.");
  Serial.println("Place magnet at 60mm and press 'm' to calibrate reference");
}

void loop() {

  if (!sensor.readData(&x, &y, &z)) return;
  char cmd = 0;

    if (Serial.available()) {
      cmd = Serial.read();

      // ignore newline / carriage return
      if (cmd == '\n' || cmd == '\r') cmd = 0;

      if (cmd != 0) {
        Serial.print("Received: ");
        Serial.println(cmd);
      }
    }



  // -------------------------
  // STEP 1: Collect Min/Max
  // -------------------------
  if (!calibrated) {
    x_min = min(x_min, x);
    x_max = max(x_max, x);

    y_min = min(y_min, y);
    y_max = max(y_max, y);

    z_min = min(z_min, z);
    z_max = max(z_max, z);

    Serial.print("Calibrating... X:");
    Serial.print(x);
    Serial.print(" Y:");
    Serial.print(y);
    Serial.print(" Z:");
    Serial.println(z);


    if (cmd == 'f') {
      // HARD IRON OFFSET
      x_offset = (x_max + x_min) / 2;
      y_offset = (y_max + y_min) / 2;
      z_offset = (z_max + z_min) / 2;

      // SOFT IRON SCALE
      float x_range = (x_max - x_min) / 2;
      float y_range = (y_max - y_min) / 2;
      float z_range = (z_max - z_min) / 2;

      float avg_range = (x_range + y_range + z_range) / 3;

      x_scale = avg_range / x_range;
      y_scale = avg_range / y_range;
      z_scale = avg_range / z_range;

      calibrated = true;

      Serial.println("Calibration DONE!");
      Serial.println("Now keep sensor fixed and press 'e' for Earth field");
    }

    delay(100);
    return;
  }

  // -------------------------
  // STEP 2: Apply Calibration
  // -------------------------
  float x_corr = (x - x_offset) * x_scale;
  float y_corr = (y - y_offset) * y_scale;
  float z_corr = (z - z_offset) * z_scale;

  // -------------------------
  // STEP 3: Earth Field Capture
  // -------------------------

  if (cmd == 'e') {
    x_earth = x_corr;
    y_earth = y_corr;
    z_earth = z_corr;

    Serial.println("Earth field captured!");
  }

  // -------------------------
  // STEP 4: Remove Earth Field
  // -------------------------
  float x_final = x_corr - x_earth;
  float y_final = y_corr - y_earth;
  float z_final = z_corr - z_earth;

  // Magnitude
  float B = sqrt(x_final*x_final + y_final*y_final + z_final*z_final);

  // ===== MAGNET REFERENCE CALIBRATION =====
  if (!magnetCalibrated) {

    if (cmd == 'm') {
      B_ref = B;
      magnetCalibrated = true;

      Serial.print("B_ref set to: ");
      Serial.println(B_ref);
      Serial.println("Starting measurement...");
    }

    Serial.print("Waiting for magnet calibration... B = ");
    Serial.println(B);

    delay(200);
    return;   // STOP further calculations until calibrated
  }


  if (B > 1) {

    // Distance from magnetometer
    float R = R_ref * pow((B_ref / B), 1.0/3.0);

    // Displacement (movement toward sensor)
    float displacement = R_ref - R;

    // Safety clamp
    if (displacement < 0) displacement = 0;

    // Limit to table range (VERY IMPORTANT)
    if (displacement > 31.0) displacement = 31.0;

    // Force from table
    float F = getForce(displacement);
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");

      String json = "{";
      json += "\"B\":" + String(B) + ",";
      json += "\"r\":" + String(displacement) + ",";
      json += "\"F\":" + String(F);
      json += "}";

      int response = http.POST(json);

      Serial.print("Sent: ");
      Serial.println(json);

      Serial.print("Response: ");
      Serial.println(response);

      http.end();
    }

    // Output
    Serial.print("Distance(mm): "); Serial.print(R);
    Serial.print("  Displacement(mm): "); Serial.print(displacement);
    Serial.print("  Force(N): "); Serial.println(F);
  }

  // -------------------------
  // OUTPUT
  // -------------------------
  // Serial.print("X: "); Serial.print(x_final);
  // Serial.print(" Y: "); Serial.print(y_final);
  // Serial.print(" Z: "); Serial.print(z_final);
  Serial.print(" |B|: "); Serial.println(B);

  delay(200);
}

