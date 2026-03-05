#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Log {
    string id, waktu, level, sumber, pesan;
};

// --- ORANG 2: Membaca Data dari File (Otomatis saat Start) ---
void loadFromFile(vector<Log>& logs, string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    
    logs.clear(); // Pastikan vector bersih sebelum diisi dari file
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // Lewati baris kosong
        stringstream ss(line);
        Log temp;
        getline(ss, temp.id, '|');
        getline(ss, temp.waktu, '|');
        getline(ss, temp.level, '|');
        getline(ss, temp.sumber, '|');
        getline(ss, temp.pesan, '|');
        logs.push_back(temp);
    }
    file.close();
}

// --- ORANG 4 (Tambahan): Input Manual Tanpa Hapus Data Lama ---
void addLogManual(vector<Log>& logs, string filename) {
    Log newLog;
    cout << "\n--- Tambah Log Baru ---" << endl;
    cout << "ID: "; cin >> newLog.id;
    cin.ignore(); 
    cout << "Waktu (YYYY-MM-DD HH:MM:SS): "; getline(cin, newLog.waktu);
    cout << "Level (INFO/WARNING/ERROR): "; getline(cin, newLog.level);
    cout << "Sumber: "; getline(cin, newLog.sumber);
    cout << "Pesan: "; getline(cin, newLog.pesan);

    logs.push_back(newLog); // Simpan ke memori

    // Menambah ke baris paling bawah file (ios::app)
    ofstream file(filename, ios::app); 
    if (file.is_open()) {
        file << newLog.id << "|" << newLog.waktu << "|" << newLog.level << "|" 
             << newLog.sumber << "|" << newLog.pesan << endl;
        file.close();
        cout << "Berhasil! Data lama tetap aman & data baru tersimpan." << endl;
    }
}

// --- ORANG 3: Fungsi Cari (Search) ---
void searchLog(const vector<Log>& logs, string kriteria, int tipe) {
    bool found = false;
    cout << "\n--- Hasil Pencarian ---" << endl;
    for (const auto& log : logs) {
        bool match = false;
        if (tipe == 1 && log.waktu.find(kriteria) != string::npos) match = true;
        if (tipe == 2 && log.level == kriteria) match = true;
        if (tipe == 3 && log.sumber == kriteria) match = true;

        if (match) {
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << endl;
            found = true;
        }
    }
    if (!found) cout << "Data tidak ditemukan." << endl;
}

int main() {
    vector<Log> listLog;
    string fileData = "data_log.txt";

    // OTOMATIS LOAD DATA LAMA
    loadFromFile(listLog, fileData);

    int pil;
    while (true) {
        cout << "\n=== MONITORING LOG SYSTEM (Ready: " << listLog.size() << " data) ===" << endl;
        cout << "1. Cari Waktu\n2. Cari Level\n3. Cari Sumber\n4. Tambah Data Baru\n5. Keluar" << endl;
        cout << "Pilih: "; cin >> pil;

        if (pil == 5) break;
        if (pil == 4) {
            addLogManual(listLog, fileData);
        } else {
            string key;
            cout << "Masukkan Kata Kunci: ";
            cin.ignore();
            getline(cin, key);
            searchLog(listLog, key, pil);
        }
    }
    return 0;
}