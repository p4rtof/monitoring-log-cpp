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

## 👥 Anggota Kelompok
- Orang 1: Spesifikasi & Dataset
- Orang 2: Implementasi Insert & File Handling
- Orang 3: Implementasi Search & Logic
- Orang 4: Main Program & Testing