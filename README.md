# IGTS_Smart_Home

🚀 **IGTS Smart Home Project**  
Proyek ini merupakan implementasi Internet of Things (IoT) yang memanfaatkan **ESP32**, **Firebase**, dan sensor untuk mengontrol servo secara otomatis berdasarkan data hujan dan jarak.
Proyek ini berkolaborasi dengan IEEE UB Student Branch, berupa proker utama yaitu IoTxIEEE Goes To School.

---

## 📂 Struktur Folder

- **IGTS_IoTxIEEE_2025.ino**  
  File utama program Arduino untuk ESP32 yang menghubungkan perangkat ke WiFi, membaca sensor hujan dan ultrasonic, mengirim data ke Firebase Realtime Database, serta mengontrol dua servo motor.
  
- **LICENSE**  
  File lisensi proyek.

- **README.md**  
  Dokumentasi deskripsi proyek.

---

## ⚙️ Fitur Utama

- **WiFi Auto Connect**  
  Menggunakan *WiFiManager* untuk konfigurasi SSID dan password WiFi tanpa hardcode.
  
- **Realtime Database**  
  Terhubung ke Firebase Realtime Database untuk menyimpan data sensor dan membaca nilai setpoint secara dinamis.
  
- **Kontrol Servo Otomatis**  
  - **Servo Hujan**: Menutup/buka berdasarkan sensor hujan.
  - **Servo Ultrasonic**: Menutup/buka berdasarkan jarak yang terdeteksi ultrasonic dan nilai setpoint dari Firebase.

---

## 🧰 Library yang Digunakan

- [WiFiManager](https://github.com/tzapu/WiFiManager)
- [Firebase ESP Client](https://github.com/mobizt/Firebase-ESP-Client)
- [ESP32Servo](https://github.com/jkb-git/ESP32Servo)

---

## 🔌 Perangkat Keras

- **ESP32**
- **Sensor Hujan**
- **Sensor Ultrasonic (HC-SR04)**
- **2x Servo Motor**

---

## 📡 Cara Kerja Singkat

1. **Koneksi WiFi**  
   Menggunakan WiFiManager, ESP32 otomatis terhubung ke WiFi.

2. **Autentikasi Firebase**  
   Registrasi Anonymous ke Firebase dengan API Key dan Database URL.

3. **Baca Sensor**  
   Membaca nilai sensor hujan & ultrasonic secara berkala.

4. **Kirim Data ke Firebase**  
   Mengirim nilai sensor ke path `/sensor6/`.

5. **Ambil Setpoint dari Firebase**  
   Membaca nilai setpoint ultrasonic dari `/setpoint6/`.

6. **Kontrol Servo**  
   - Servo hujan bergerak sesuai intensitas hujan.
   - Servo ultrasonic bergerak sesuai jarak & setpoint.

---

## 📌 Catatan

- Ganti `API_KEY` dan `DATABASE_URL` dengan milikmu di Firebase.
- Pastikan koneksi WiFi stabil.
- Sesuaikan `rainThreshold` dan `setpointUltra` sesuai kondisi lapangan.

---

## 📜 Lisensi

Proyek ini berlisensi sesuai file [LICENSE](./LICENSE).

---

## 👨‍💻 Kontribusi

Pull request sangat diterima! Jangan ragu untuk mengajukan perbaikan atau penambahan fitur.

---

**© IGTS IoTxIEEE 2025**
