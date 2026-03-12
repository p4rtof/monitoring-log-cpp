#include <iostream>      // Buat input-output standar kayak cin & cout
#include <vector>        // Buat pakai struktur data Vector (array dinamis)
#include <fstream>       // Buat baca dan nulis ke file (.txt)
#include <sstream>       // Buat motong-motong string (teks)
#include <unordered_map> // Buat pakai struktur data Hash Table
#include <chrono>        // Buat ngitung waktu (stopwatch)

using namespace std; // Biar nggak repot ngetik std:: terus-terusan

struct Log
{                                           // Bikin cetakan data (struct) buat satu baris log
    string id, waktu, level, sumber, pesan; // Variabel penyimpan datanya
};

// Siapin 2 struktur data buat dibandingin
vector<Log> listLog;                         // Wadah 1: Vector (nyimpan semua data berurutan)
unordered_map<string, vector<Log>> mapLevel; // Wadah 2: Hash Table (ngelompokin data berdasarkan Level)

void bacaDataFile(string filename)
{                            // Fungsi buat baca data dari file pas awal jalan
    ifstream file(filename); // Buka file txt-nya
    if (!file.is_open())
        return; // Kalau file nggak ada, yaudah batalin (keluar fungsi)

    string line; // Siapin variabel buat nyimpen teks per baris
    while (getline(file, line))
    { // Looping: baca file baris demi baris sampai habis
        if (line.empty())
            continue;          // Kalau barisnya kosong, lewatin aja
        stringstream ss(line); // Masukin sebaris teks ke pemotong string
        Log temp;              // Bikin log sementara buat nampung potongan teks

        // Potong teks tiap ketemu huruf '|' lalu masukin ke variabelnya
        getline(ss, temp.id, '|');
        getline(ss, temp.waktu, '|');
        getline(ss, temp.level, '|');
        getline(ss, temp.sumber, '|');
        getline(ss, temp.pesan, '|');

        // Simpan data yang udah dipotong ke 2 struktur data kita
        listLog.push_back(temp);              // Masukin ke Vector
        mapLevel[temp.level].push_back(temp); // Masukin ke Hash Table (dikunci pakai Level-nya)
    }
    file.close(); // Tutup filenya biar memori aman
}

void cariPakaiHashTable(string targetLevel)
{ // Fungsi nyari data pakai Hash Table (Khusus Level)
    // Mulai hitung waktu (Stopwatch ON)
    auto start = chrono::high_resolution_clock::now();

    // Proses pencarian kilat di Hash Table (langsung lompat ke kuncinya)
    auto it = mapLevel.find(targetLevel);
    // Cek apakah datanya ketemu dan isinya nggak kosong
    bool ketemu = (it != mapLevel.end() && !it->second.empty());

    // Berhenti hitung waktu (Stopwatch OFF) sebelum proses print (biar murni waktu komputasi)
    auto end = chrono::high_resolution_clock::now();
    // Hitung durasi pencariannya dalam satuan mikrodetik
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Mulai nampilin data ke layar
    cout << "\n--- Hasil Pencarian Level: " << targetLevel << " ---\n";
    if (ketemu)
    { // Kalau datanya ada
        // Looping buat nampilin semua log di level yang dicari
        for (const auto &log : it->second)
        {
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << "\n";
        }
        cout << "\nTotal data ketemu: " << it->second.size() << " log.\n"; // Print total data
    }
    else
    {
        cout << "Data nggak ketemu.\n"; // Kalau datanya nggak ada
    }

    // Nampilin waktu pencariannya
    cout << "Waktu murni pencarian Hash Table: " << durasi << " mikrodetik\n";
}

// 1. Fungsi Tambah Log dari User
void tambahLog()
{
    Log baru; // Bikin log kosong baru
    // Minta user masukin data satu-satu
    cout << "ID: ";
    cin >> baru.id;
    cin.ignore(); // cin.ignore() biar enter-nya nggak ngaco ke input selanjutnya
    cout << "Waktu (YYYY-MM-DD): ";
    getline(cin, baru.waktu);
    cout << "Level (INFO/ERROR/WARNING): ";
    getline(cin, baru.level);
    cout << "Sumber: ";
    getline(cin, baru.sumber);
    cout << "Pesan: ";
    getline(cin, baru.pesan);

    // Masukin log baru ke Vector (Memory)
    listLog.push_back(baru);
    // Masukin juga ke Hash Table biar langsung ke-update
    mapLevel[baru.level].push_back(baru);

    // Tulis data barunya ke file txt (ios::app biar nambah di baris paling bawah, bukan nimpa)
    ofstream file("data_log.txt", ios::app);
    // Format tulisannya dipisah pakai '|' lagi
    file << baru.id << "|" << baru.waktu << "|" << baru.level << "|" << baru.sumber << "|" << baru.pesan << "\n";
    cout << "Log berhasil tersimpan!\n";
}

// 2. Fungsi Cari & Tampil Log (Pakai Vector)
// Pilihan: 1 = Waktu, 2 = Level, 3 = Sumber
void cariLog(int pilihan, string keyword)
{
    vector<Log> hasilCari; // Wadah sementara buat nyimpen hasil ketemu

    // Mulai hitung waktu (Stopwatch ON)
    auto start = chrono::high_resolution_clock::now();

    // Proses pencarian manual di Vector (ngecek satu per satu dari atas ke bawah)
    for (const auto &log : listLog)
    {
        bool cocok = false; // Flag penanda cocok atau nggak
        // Cek sesuai pilihan user
        if (pilihan == 1 && log.waktu.find(keyword) != string::npos)
            cocok = true; // Nyari waktu (bisa sebagian kata)
        else if (pilihan == 2 && log.level == keyword)
            cocok = true; // Nyari level (harus sama persis)
        else if (pilihan == 3 && log.sumber == keyword)
            cocok = true; // Nyari sumber (harus sama persis)

        if (cocok)
        {
            hasilCari.push_back(log); // Kalau cocok, simpan ke wadah sementara dulu
        }
    }

    // Berhenti hitung waktu (Stopwatch OFF) tepat setelah loop selesai ngecek
    auto end = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count(); // Hitung mikrodetik

    // Mulai nampilin data ke layar
    cout << "\n--- Hasil Pencarian ---\n";
    if (!hasilCari.empty())
    { // Kalau wadah sementaranya nggak kosong
        for (const auto &log : hasilCari)
        { // Print semua isinya
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << "\n";
        }
        cout << "\nTotal data ketemu: " << hasilCari.size() << " log.\n";
    }
    else
    {
        cout << "Yah, log gak ketemu nih.\n";
    }

    // Nampilin waktu komputasi Vector-nya
    cout << "Waktu murni pencarian Vector: " << durasi << " mikrodetik\n";
}

int main()
{
    // 1. Load data lama dari file txt pas program baru jalan
    bacaDataFile("data_log.txt");

    int menu; // Variabel buat milih menu
    while (true)
    { // Looping terus-terusan sampai user milih Keluar
        // Tampilan menu utama
        cout << "\n=== MENU LOG SYSTEM (Total: " << listLog.size() << " data) ===\n";
        cout << "1. Tambah Log\n2. Cari Waktu\n3. Cari Level\n4. Cari Sumber\n5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu; // Baca pilihan user

        if (menu == 5)
        { // Kalau pilih 5, program berhenti
            cout << "Program selesai!\n";
            break; // Keluar dari looping while
        }

        if (menu == 1)
        { // Kalau pilih 1, panggil fungsi tambah
            tambahLog();
        }
        else if (menu == 3)
        {
            // KHUSUS MENU 3 (Cari Level), KITA PAKAI HASH TABLE BIAR NGEBUT
            string cari;
            cout << "Masukkan Level (INFO/WARNING/ERROR): ";
            cin >> cari;
            cariPakaiHashTable(cari); // Panggil pencarian Hash Table
        }
        else if (menu == 2 || menu == 4)
        {
            // MENU 2 (Waktu) & 4 (Sumber) TETAP PAKAI VECTOR
            string cari;
            cout << "Masukkan kata kunci: ";
            cin >> cari;

            // Konversi nomor menu ke nomor pilihan fungsi cariLog
            if (menu == 2)
                cariLog(1, cari); // 1 untuk nyari Waktu
            if (menu == 4)
                cariLog(3, cari); // 3 untuk nyari Sumber
        }
        else
        {
            cout << "Menu gak ada, ketik yang bener yaa!\n"; // Kalau inputnya ngaco
        }
    }

    return 0; // Beres
}