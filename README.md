# Sistem Monitoring & Log Aktivitas Aplikasi

Proyek ini adalah sistem backend sederhana untuk mengelola log aktivitas (login, error, API request) menggunakan bahasa C++.

## 📋 Progres Minggu ke-7
- [x] Spesifikasi sistem & skenario aktivitas.
- [x] Implementasi struktur data `std::vector`.
- [x] Dataset log dummy (`data_log.txt`).
- [x] Fungsi Insert & Search data.

## 🚀 Fitur Utama
1. **Load Data**: Membaca log otomatis dari file `.txt`.
2. **Search**: Mencari log berdasarkan Waktu, Level (INFO/WARN/ERROR), dan Sumber.
3. **Add Log**: Menambah data log baru secara manual via terminal tanpa menghapus data lama.

## 🛠️ Cara Menjalankan
1. Pastikan `data_log.txt` ada di folder yang sama.
2. Compile: `g++ main.cpp -o main`
3. Run: `.\main.exe`

## 👥 Anggota Kelompok 9 P4 Struktur Data
1. Fadhla (M0403241004)
2. Avriell Shianne Chrisly (M0403241027)
3. Mirabel Nasywa Rajendraputri (M0403241067)
4. M. Revandi Aridya Pohan (M0403241077)
