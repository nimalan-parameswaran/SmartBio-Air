/*
 * MYOSA Bio-Reactor & Industry Monitor (Fixed & Optimized)
 * Features:
 * - 4x Gas Sensors (Composition Analysis)
 * - MPU6050 (Motor AI + Temperature)
 * - APDS9960 (Algae AI + Green Color/Light Analysis)
 * - BMP180 (Pressure + Altitude)
 * - Firebase Realtime Database
 */

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// MYOSA Libraries
#include <LightProximityAndGesture.h>
#include <AccelAndGyro.h>
#include <BarometricPressure.h>

// Edge Impulse Models
// NOTE: Ensure 'edge-impulse-sdk' is deleted from ONE of these library folders to avoid conflicts.
#include <Algaegroww_inferencing.h>
#include <MYOSA-6vDMP-Fault-Detection_inferencing.h>

// --- CONFIGURATION --- //
#define WIFI_SSID "NIMALANPC"
#define WIFI_PASSWORD "9876543210"
#define FIREBASE_API_KEY "AIzaSyBoScgpNKDnejoGCB95XIcq70MJO85s81g"
#define FIREBASE_DATABASE_URL "https://smartbioair-v1-default-rtdb.asia-southeast1.firebasedatabase.app"

// Gas Pins (ADC1)
#define PIN_MQ135 36 
#define PIN_MQ2   39 
#define PIN_MQ7   34
#define PIN_MQ3   35

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Objects
LightProximityAndGesture lpg;
AccelAndGyro ag;
BarometricPressure bmp; 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Data Structure
struct SystemState {
  // Gas Raw Values (0-100)
  uint8_t mq135;
  uint8_t mq2;
  uint8_t mq7;
  uint8_t mq3;
  
  // Environment
  float tempC;      // From MPU6050
  float pressure;   // From BMP
  float altitude;   // From BMP
  
  // Color/Light
  uint16_t green;   // Green Channel
  uint16_t ambient; // Lux/Clear
  
  // AI Predictions
  uint8_t algaeHealth; // 0=Good, 1=Bad
  uint8_t motorHealth; // 0=Normal, 1=Fault
};
SystemState sys;

bool wifiConnected = false;
unsigned long lastSend = 0;

// --- SENSOR HELPER FUNCTIONS --- //

// Read MPU6050 Temperature directly via I2C (Register 0x41)
float readMPUTemperature() {
  Wire.beginTransmission(0x69); // MPU6050 Address
  Wire.write(0x41);             // TEMP_OUT_H register
  Wire.endTransmission();
  Wire.requestFrom(0x69, 2);
  if (Wire.available() == 2) {
    int16_t raw = (Wire.read() << 8) | Wire.read();
    return (raw / 340.0) + 36.53; // Standard MPU6050 formula
  }
  return 0.0;
}

uint8_t readGas(int pin) {
  int val = analogRead(pin);
  if (val < 50) return 0;
  // Map 12-bit ADC (0-4095) to 0-100 scale for analysis
  return map(val, 0, 4095, 0, 100); 
}

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  display.print(F("WiFi...")); display.display();
  int t = 0;
  while (WiFi.status() != WL_CONNECTED && t < 20) { delay(500); t++; }
  
  if (WiFi.status() == WL_CONNECTED) {
    display.println(F("OK"));
    config.api_key = FIREBASE_API_KEY;
    config.database_url = FIREBASE_DATABASE_URL;
    Firebase.signUp(&config, &auth, "", "");
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    wifiConnected = true;
  } else {
    display.println(F("Fail"));
  }
  display.display();
}

// --- MAIN TASKS --- //

void readAllSensors() {
  // 1. Gas Composition
  sys.mq135 = readGas(PIN_MQ135);
  sys.mq2   = readGas(PIN_MQ2);
  sys.mq7   = readGas(PIN_MQ7);
  sys.mq3   = readGas(PIN_MQ3);

  // 2. MPU Environment (Temperature)
  sys.tempC = readMPUTemperature();

  // 3. BMP Environment (Pressure/Alt)
  if (bmp.ping()) {
    sys.pressure = bmp.getPressurePascal(false); // Returns Pa, false=no print
    
    // FIX APPLIED HERE: Added sea level pressure (1013.25) and false for silent mode
    sys.altitude = bmp.getAltitude(1013.25, false); 
  } else {
    sys.pressure = 0;
    sys.altitude = 0;
  }

  // 4. Light & Color (Green Analysis)
  sys.green = lpg.getGreenProportion(); 
  
  // FIX APPLIED HERE: Use public getAmbientLight() instead of private readAmbientLight()
  sys.ambient = lpg.getAmbientLight(false); 
}

void runAI() {
  // --- ALGAE MODEL ---
  uint16_t r = lpg.getRedProportion();
  uint16_t g = lpg.getGreenProportion();
  uint16_t b = lpg.getBlueProportion();
  
  // Snapshot for inference
  float algae_features[] = { (float)r, (float)g, (float)b };
  signal_t signal_algae;
  numpy::signal_from_buffer(algae_features, 3, &signal_algae);
  
  ei_impulse_result_t result_algae = { 0 };
  run_classifier(&signal_algae, &result_algae, false);
  
  // Index 1 = Bad (Check your Impulse)
  sys.algaeHealth = (result_algae.classification[1].value > 0.6) ? 1 : 0;

  // --- MOTOR MODEL ---
  float imu_buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {0};
  
  // Fill buffer (Blocking ~1-2 sec)
  for (int i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i += 6) {
    uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);
    imu_buffer[i+0] = ag.getAccelX(false);
    imu_buffer[i+1] = ag.getAccelY(false);
    imu_buffer[i+2] = ag.getAccelZ(false);
    imu_buffer[i+3] = ag.getGyroX(false);
    imu_buffer[i+4] = ag.getGyroY(false);
    imu_buffer[i+5] = ag.getGyroZ(false);
    while (micros() < next_tick);
  }

  signal_t signal_mot;
  numpy::signal_from_buffer(imu_buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal_mot);
  
  ei_impulse_result_t result_mot = { 0 };
  run_classifier(&signal_mot, &result_mot, false);

  sys.motorHealth = (result_mot.classification[1].value > 0.5) ? 1 : 0;
  
  #if EI_CLASSIFIER_HAS_ANOMALY == 1
  if (result_mot.anomaly > 0.3) sys.motorHealth = 1;
  #endif
}

void sendFirebase() {
  if (!wifiConnected || !Firebase.ready()) return;

  FirebaseJson json;
  
  // GAS COMPOSITION
  json.set("gas/mq135", sys.mq135);
  json.set("gas/mq2", sys.mq2);
  json.set("gas/mq7", sys.mq7);
  json.set("gas/mq3", sys.mq3);
  
  // ALGAE ANALYSIS (Bio-Reactor)
  json.set("algae/health", sys.algaeHealth == 0 ? "Good" : "Bad");
  json.set("algae/temp_c", sys.tempC); // Water/Ambient Temp
  json.set("algae/green_idx", sys.green);
  json.set("algae/light_lux", sys.ambient);
  
  // ENVIRONMENT (Barometric)
  json.set("env/pressure", sys.pressure);
  json.set("env/altitude", sys.altitude);
  
  // MOTOR
  json.set("motor/status", sys.motorHealth == 0 ? "Normal" : "Fault");
  
  json.set("ts", millis()); // Timestamp

  if (Firebase.RTDB.pushJSON(&fbdo, "/bio_monitor", &json)) {
    // Success - optional serial print
  }
}

void updateOLED() {
  display.clearDisplay();

  // ===== Header =====
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("SmartBio AIR"));
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

  // ===== Line positions =====
  int y = 14;

  // Air Quality (Max Gas)
  uint8_t maxGas = max(sys.mq135, max(sys.mq2, sys.mq7));
  display.setCursor(0, y);
  display.print(F("AirQual: "));
  if (maxGas < 20)      display.println(F("GOOD"));
  else if (maxGas < 50) display.println(F("FAIR"));
  else                  display.println(F("POOR"));
  y += 11;
  // Motor Status
  display.setCursor(0, y);
  display.print(F("Motor: "));
  display.println(sys.motorHealth ? F("ERR") : F("OK"));
  y += 11;

  // Algae Status
  display.setCursor(0, y);
  display.print(F("Algae: "));
  display.println(sys.algaeHealth ? F("BAD") : F("OK"));
  y += 11;

  // Temperature
  display.setCursor(0, y);
  display.print(F("Temp: "));
  display.print(sys.tempC, 1);
  display.println(F(" C"));
  y += 11;

  // Altitude
  display.setCursor(0, y);
  display.print(F("Alt: "));
  display.print((int)sys.altitude);
  display.println(F(" m"));

  display.display();
}


void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Init OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("Init Sensors..."));
  display.display();

  // Init MYOSA Modules
  lpg.begin();
  lpg.enableAmbientLightSensor(ENABLE);
  ag.begin(); // MPU6050
  bmp.begin(); // BMP180/280

  initWiFi();
}

void loop() {
  readAllSensors();
  runAI();
  updateOLED();
  
  // Send data every 3 seconds
  if (millis() - lastSend > 3000) {
    sendFirebase();
    lastSend = millis();
  }
}