# 📊 Sistem Monitoring & Log Aktivitas Aplikasi

Proyek *backend* simpel menggunakan C++ untuk mengelola log aktivitas sistem (seperti *login*, *error*, dan *API request*) sekaligus mengukur efisiensi kecepatan algoritma pencariannya!

## 📋 Update Progres (Minggu 1-7)
- [x] Penentuan spesifikasi & skenario aktivitas.
- [x] Implementasi 2 Struktur Data utama: `std::vector` & `std::unordered_map` (*Hash Table*).
- [x] Pembuatan dataset log *dummy* (`data_log.txt`).
- [x] Fitur *Insert* & *Search* data.
- [x] *Benchmarking* waktu komputasi pencarian menggunakan *library* `<chrono>`.

## 🚀 Fitur Utama
1. **Load Data (*In-Memory*)**: Membaca ribuan baris log secara otomatis dari *file* `.txt` ke RAM saat program berjalan.
2. **Search Cepat (*Hash Table*)**: Mencari log berdasarkan kategori **Level** (INFO/WARN/ERROR) dengan waktu akses seketika / *constant time* O(1).
3. **Search Fleksibel (*Vector*)**: Mencari log berdasarkan **Waktu** dan **Sumber** dengan dukungan *pencarian parsial (substring)*. Cukup ketik sebagian kata, data langsung ketemu! O(n).
4. **Add Log (*Insert*)**: Menambah log baru via terminal. Data otomatis tersimpan persisten ke *file* `.txt` dan struktur data di memori langsung ter-*update* O(1).
5. **Cek Performa (*Stopwatch*)**: Menampilkan durasi komputasi setiap kali pencarian dieksekusi (dalam satuan mikrodetik) untuk pembuktian performa.

## 🛠️ Cara Menjalankan Program
1. Pastikan *file* `data_log.txt` berada di direktori yang sama dengan *file* program (atau di dalam folder `output` sesuai *setup* lokalmu).
2. *Compile* kode C++: 
   ```bash
   g++ main.cpp -o main

## 👥 Anggota Kelompok 9 (P4 Struktur Data)
1. Fadhla (M0403241004)
2. Avriell Shianne Chrisly (M0403241027)
3. Mirabel Nasywa Rajendraputri (M0403241067)
4. M. Revandi Aridya Pohan (M0403241077)
