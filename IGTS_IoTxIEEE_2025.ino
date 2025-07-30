#include <WiFiManager.h>              // https://github.com/tzapu/WiFiManager
#include <Firebase_ESP_Client.h>      // https://github.com/mobizt/Firebase-ESP-Client
#include <ESP32Servo.h>

// Tambahkan TokenHelper dan RTDBHelper untuk manajemen token
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// GANTI DENGAN DATA PRIBADI DI FILE TERPISAH ATAU GUNAKAN SECRET
#define API_KEY "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL "https://your-project-id.firebaseio.com/"

// Objek Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variabel Global
bool signupOK = false;
unsigned long sendDataPrevMillis = 0;

// Servo dan Pin
Servo servoRain;
Servo servoUltra;

const int servoRainPin = 26;
const int servoUltraPin = 25;

const int rainSensorPin = 33;
const int trigPin = 14;
const int echoPin = 27;

int rainThreshold = 3500; // Nilai threshold hujan
int setpointUltra = 10;   // Nilai default setpoint dari Firebase

// Fungsi baca sensor Ultrasonic
long readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  Serial.begin(115200);

  // Setup Servo
  servoRain.attach(servoRainPin);
  servoUltra.attach(servoUltraPin);

  // Setup pin sensor ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // WiFi Manager setup untuk WiFi otomatis
  WiFiManager wm;
  bool res = wm.autoConnect("SmartHomeAP", "password1234"); // Ganti SSID & password AP sementara
  if (!res) {
    Serial.println("Gagal koneksi WiFi, restart ESP...");
    ESP.restart();
  } else {
    Serial.println("WiFi Terkoneksi!");
  }

  // Firebase setup
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp OK");
    signupOK = true;
  } else {
    Serial.printf("Firebase SignUp Gagal: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 10000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Baca Sensor
    int rainValue = analogRead(rainSensorPin);
    long distance = readUltrasonicDistance();

    Serial.print("Rain Value: ");
    Serial.println(rainValue);
    Serial.print("Distance: ");
    Serial.println(distance);

    // Kirim data sensor ke Firebase
    if (Firebase.RTDB.setInt(&fbdo, "/sensor6/rain", rainValue)) {
      Serial.println("Rain data sent.");
    } else {
      Serial.println("Failed to send rain data: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setInt(&fbdo, "/sensor6/distance", distance)) {
      Serial.println("Distance data sent.");
    } else {
      Serial.println("Failed to send distance data: " + fbdo.errorReason());
    }

    // Ambil setpoint ultrasonic dari Firebase
    if (Firebase.RTDB.getString(&fbdo, "/setpoint6/ultrasonic")) {
      String angkaStr = fbdo.stringData();
      int angka = angkaStr.toInt();
      setpointUltra = angka;
      Serial.print("Setpoint dari Firebase: ");
      Serial.println(angka);
    } else {
      Serial.println("Gagal ambil setpoint ultrasonic: " + fbdo.errorReason());
    }

    // Kontrol Servo Hujan
    if (rainValue < rainThreshold) {
      servoRain.write(0);
      Serial.println("Servo Hujan: Tertutup (karena hujan)");
    } else {
      servoRain.write(90);
      Serial.println("Servo Hujan: Terbuka");
    }

    // Kontrol Servo Ultrasonic
    if (distance < setpointUltra) {
      servoUltra.write(90);
      Serial.println("Servo Ultrasonic: Tertutup (jarak dekat)");
    } else {
      servoUltra.write(0);
      Serial.println("Servo Ultrasonic: Terbuka");
    }
  }
}
