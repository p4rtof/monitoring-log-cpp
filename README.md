# Sistem Monitoring & Log Aktivitas Aplikasi

Proyek backend simpel pakai C++ buat kelola log aktivitas (login, error, API request) plus ngukur kecepatan pencariannya!

## 📋 Update Progres Minggu 1-7
- [x] Spesifikasi & skenario aktivitas.
- [x] Pakai 2 Struktur Data: `std::vector` & `std::unordered_map` (Hash Table).
- [x] Dataset log dummy (`data_log.txt`).
- [x] Fitur Insert & Search data.
- [x] Hitung waktu pencarian (*stopwatch*) pakai library `<chrono>`.

## 🚀 Fitur Utama
1. **Load Data**: Baca log otomatis dari `.txt`.
2. **Search Cepat (Hash Table)**: Nyari log berdasarkan **Level** (INFO/WARN/ERROR) secepat kilat.
3. **Search Biasa (Vector)**: Nyari log berdasarkan **Waktu** dan **Sumber**.
4. **Add Log**: Nambah log baru via terminal (data lama aman, Hash Table & Vector otomatis ke-update).
5. **Cek Performa**: Nampilin durasi waktu tiap kali nyari data (dalam mikrodetik) buat bahan laporan.

## 🛠️ Cara Menjalankan
1. Pastiin file `data_log.txt` ada di folder yang sama dengan `main.cpp`.
2. Compile: `g++ main.cpp -o main`
3. Run: `.\main.exe`

## 👥 Anggota Kelompok 9 (P4 Struktur Data)
1. Fadhla (M0403241004)
2. Avriell Shianne Chrisly (M0403241027)
3. Mirabel Nasywa Rajendraputri (M0403241067)
4. M. Revandi Aridya Pohan (M0403241077)