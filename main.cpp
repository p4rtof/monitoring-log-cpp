#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <chrono>

using namespace std;

struct Log {
    string id, waktu, level, sumber, pesan;
};

// Siapin 2 struktur data buat dibandingin
vector<Log> listLog;
unordered_map<string, vector<Log>> mapLevel; 

void bacaDataFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Log temp;
        getline(ss, temp.id, '|');
        getline(ss, temp.waktu, '|');
        getline(ss, temp.level, '|');
        getline(ss, temp.sumber, '|');
        getline(ss, temp.pesan, '|');
        
        // Simpan ke Vector & Hash Table
        listLog.push_back(temp);
        mapLevel[temp.level].push_back(temp); 
    }
    file.close();
}

void cariPakaiHashTable(string targetLevel) {
    // Mulai hitung waktu (Stopwatch ON)
    auto start = chrono::high_resolution_clock::now();

    // Proses pencarian di Hash Table
    auto it = mapLevel.find(targetLevel);
    bool ketemu = (it != mapLevel.end() && !it->second.empty());

    // Berhenti hitung waktu (Stopwatch OFF) tepat setelah nyari (sebelum nge-print)
    auto end = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Mulai nampilin data
    cout << "\n--- Hasil Pencarian Level: " << targetLevel << " ---\n";
    if (ketemu) {
        // Looping untuk nampilin semua log di level tersebut
        for (const auto& log : it->second) {
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << "\n";
        }
        cout << "\nTotal data ketemu: " << it->second.size() << " log.\n";
    } else {
        cout << "Data nggak ketemu.\n";
    }
    
    // Nampilin waktu pencariannya
    cout << "Waktu murni pencarian Hash Table: " << durasi << " mikrodetik\n";
}
// 1. Fungsi Tambah Log dari User
void tambahLog() {
    Log baru;
    cout << "ID: "; cin >> baru.id; cin.ignore();
    cout << "Waktu (YYYY-MM-DD): "; getline(cin, baru.waktu);
    cout << "Level (INFO/ERROR): "; getline(cin, baru.level);
    cout << "Sumber: "; getline(cin, baru.sumber);
    cout << "Pesan: "; getline(cin, baru.pesan);
    
    // Masukin ke Vector (Memory)
    listLog.push_back(baru);
    mapLevel[baru.level].push_back(baru);
    
    // Tulis ke file txt
    ofstream file("data_log.txt", ios::app);
    file << baru.id << "|" << baru.waktu << "|" << baru.level << "|" << baru.sumber << "|" << baru.pesan << "\n";
    cout << "Log mantap tersimpan!\n";
}

// 2. Fungsi Cari & Tampil Log
// Pilihan: 1 = Waktu, 2 = Level, 3 = Sumber
// 2. Fungsi Cari & Tampil Log (Pakai Vector)
// Pilihan: 1 = Waktu, 2 = Level, 3 = Sumber
void cariLog(int pilihan, string keyword) {
    vector<Log> hasilCari; // Wadah sementara buat nyimpen hasil ketemu

    // Mulai hitung waktu (Stopwatch ON)
    auto start = chrono::high_resolution_clock::now();
    
    // Proses pencarian murni di Vector
    for (const auto& log : listLog) {
        bool cocok = false;
        if (pilihan == 1 && log.waktu.find(keyword) != string::npos) cocok = true;
        else if (pilihan == 2 && log.level == keyword) cocok = true;
        else if (pilihan == 3 && log.sumber == keyword) cocok = true;

        if (cocok) {
            hasilCari.push_back(log); // Simpan dulu, jangan di-print di sini
        }
    }
    
    // Berhenti hitung waktu (Stopwatch OFF) tepat setelah loop selesai
    auto end = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Mulai nampilin data ke layar (Stopwatch udah aman dimatikan)
    cout << "\n--- Hasil Pencarian ---\n";
    if (!hasilCari.empty()) {
        for (const auto& log : hasilCari) {
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << "\n";
        }
        cout << "\nTotal data ketemu: " << hasilCari.size() << " log.\n";
    } else {
        cout << "Yah, log nggak ketemu nih.\n";
    }

    // Nampilin waktu pencarian Vector-nya
    cout << "Waktu murni pencarian Vector: " << durasi << " mikrodetik\n";
}

int main() {
    // 1. Load data lama pas program baru jalan
    bacaDataFile("data_log.txt");

    int menu;
    while (true) {
        cout << "\n=== MENU LOG SYSTEM (Total: " << listLog.size() << " data) ===\n";
        cout << "1. Tambah Log\n2. Cari Waktu\n3. Cari Level\n4. Cari Sumber\n5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        if (menu == 5) {
            cout << "Program selesai. Babay!\n";
            break;
        }

        if (menu == 1) {
            tambahLog();
        } else if (menu == 3) { 
            // KHUSUS MENU 3 (Cari Level), KITA PAKAI HASH TABLE BIAR NGEBUT
            string cari;
            cout << "Masukkan Level (INFO/WARNING/ERROR): ";
            cin >> cari;
            cariPakaiHashTable(cari); 

        } else if (menu == 2 || menu == 4) { 
            // MENU 2 (Waktu) & 4 (Sumber) TETAP PAKAI VECTOR
            string cari;
            cout << "Masukkan kata kunci: ";
            cin >> cari;
            
            if (menu == 2) cariLog(1, cari); // 1 untuk Waktu
            if (menu == 4) cariLog(3, cari); // 3 untuk Sumber
            
        } else {
            cout << "Menu nggak ada, ketik yang bener dong!\n";
        }
    }
    
    return 0;
}