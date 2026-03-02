#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream> 
#include <sstream> 
#include <chrono> 

using namespace std;
using namespace std::chrono;

// === TUGAS ORANG 1: DEFINISI STRUKTUR DATA ===
struct Log {
    int id;
    string timestamp;
    string level;
    string source;
    string message;
};

// === TUGAS ORANG 1: GENERATOR DATA DUMMY ===
void generateDummyData(vector<Log>& container, int jumlah) {
    string levels[] = {"INFO", "WARNING", "ERROR"};
    string sources[] = {"AuthSystem", "PaymentGateway", "InventoryDB", "UserSvc"};
    
    for (int i = 1; i <= jumlah; i++) {
        Log temp;
        temp.id = i;
        temp.timestamp = "2026-03-02 23:50:0" + to_string(i % 10); // Biar waktunya agak beda
        temp.level = levels[rand() % 3];        
        temp.source = sources[rand() % 4];      
        temp.message = "Aktivitas sistem nomor " + to_string(i);
        
        container.push_back(temp);
    }
    cout << "Berhasil membuat " << jumlah << " data log dummy." << endl;
}

// === TUGAS ORANG 2: FUNGSI SIMPAN KE FILE TXT ===
void saveToTxt(const vector<Log>& container, string namaFile) {
    ofstream fileKeluar(namaFile);
    if (fileKeluar.is_open()) {
        for (const auto& log : container) {
            fileKeluar << log.id << "|" << log.timestamp << "|" << log.level << "|" 
                       << log.source << "|" << log.message << endl;
        }
        fileKeluar.close(); 
    }
}

// === TUGAS ORANG 3: FUNGSI BACA & CARI DARI FILE TXT ===
void loadFromTxt(vector<Log>& container, string namaFile) {
    ifstream fileMasuk(namaFile);
    string baris;
    if (fileMasuk.is_open()) {
        container.clear(); 
        while (getline(fileMasuk, baris)) {
            stringstream ss(baris);
            Log temp;
            string idStr, timestamp, level, source, message;

            getline(ss, idStr, '|');
            getline(ss, timestamp, '|');
            getline(ss, level, '|');
            getline(ss, source, '|');
            getline(ss, message, '|');

            temp.id = stoi(idStr);
            temp.timestamp = timestamp;
            temp.level = level;
            temp.source = source;
            temp.message = message;

            container.push_back(temp);
        }
        fileMasuk.close();
    }
}

// Fungsi Pencarian Tambahan (Syarat Topik 9)
void searchByLevel(const vector<Log>& container, string targetLevel) {
    cout << "\n--- MENCARI LOG LEVEL: " << targetLevel << " ---" << endl;
    for (const auto& log : container) {
        if (log.level == targetLevel) {
            cout << "ID: " << log.id << " | Modul: " << log.source << " | Pesan: " << log.message << endl;
        }
    }
}

void searchBySource(const vector<Log>& container, string targetSource) {
    cout << "\n--- MENCARI LOG MODUL: " << targetSource << " ---" << endl;
    for (const auto& log : container) {
        if (log.source == targetSource) {
            cout << "ID: " << log.id << " | Level: " << log.level << " | Pesan: " << log.message << endl;
        }
    }
}

void showStatistics(const vector<Log>& container) {
    int info = 0, warning = 0, error = 0;
    for (const auto& log : container) {
        if (log.level == "INFO") info++;
        else if (log.level == "WARNING") warning++;
        else if (log.level == "ERROR") error++;
    }
    cout << "\n=== STATISTIK LOG ===" << endl;
    cout << "INFO: " << info << " | WARNING: " << warning << " | ERROR: " << error << endl;
}

// === TUGAS ORANG 4: FUNGSI PENGUKUR WAKTU ===
void hitungPerforma(vector<Log>& gudang, string namaFile) {
    cout << "\n=== MULAI UJI PERFORMA ===" << endl;
    
    // Ukur Simpan
    auto mulaiSimpan = high_resolution_clock::now();
    saveToTxt(gudang, namaFile); 
    auto selesaiSimpan = high_resolution_clock::now();
    
    // Ukur Cari
    auto mulaiCari = high_resolution_clock::now();
    searchByLevel(gudang, "ERROR"); 
    auto selesaiCari = high_resolution_clock::now();

    duration<double, milli> durasiSimpan = selesaiSimpan - mulaiSimpan;
    duration<double, milli> durasiCari = selesaiCari - mulaiCari;

    cout << "\n=== HASIL WAKTU EKSEKUSI ===" << endl;
    cout << "Waktu Simpan (Insert): " << durasiSimpan.count() << " ms" << endl;
    cout << "Waktu Cari (Search): " << durasiCari.count() << " ms" << endl;
}

int main() {
    vector<Log> gudangLog;
    string namaFile = "database_log.txt";
    
    // 1. Generate 10.000 data dummy biar kerasa performanya
    generateDummyData(gudangLog, 10000); 

    // 2. Jalankan fungsi hitung waktu (Tugas Orang 4 mencakup insert & search)
    hitungPerforma(gudangLog, namaFile);

    // 3. Tes fungsi baca file dan tampilkan statistik
    loadFromTxt(gudangLog, namaFile);
    showStatistics(gudangLog);
    
    // 4. Tes fitur pencarian wajib
    // searchBySource(gudangLog, "AuthSystem"); // Hilangkan tanda komen (//) untuk ngetes
    
    return 0;
}