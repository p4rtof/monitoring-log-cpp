#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Log {
    string id, waktu, level, sumber, pesan;
};

// --- TUGAS ORANG 2: Insert Data ---
void insertData(vector<Log>& logs, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File " << filename << " tidak ditemukan!" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
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

// --- TUGAS ORANG 3: Fungsi Search (User Input) ---
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
    if (!found) cout << "Data tidak ditemukan untuk kata kunci: " << kriteria << endl;
}

// --- TUGAS ORANG 4: Main Program dengan Menu ---
int main() {
    vector<Log> listLog;
    insertData(listLog, "data_log.txt"); 

    int pilihan;
    string keyword;

    while (true) {
        cout << "\n=== MENU MONITORING LOG ===" << endl;
        cout << "1. Cari berdasarkan Waktu" << endl;
        cout << "2. Cari berdasarkan Level (INFO/WARNING/ERROR)" << endl;
        cout << "3. Cari berdasarkan Sumber Modul" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        if (pilihan == 4) break;

        cout << "Masukkan kata kunci pencarian: ";
        cin.ignore(); // Membersihkan buffer
        getline(cin, keyword);

        searchLog(listLog, keyword, pilihan);
        
        cout << "\nTekan Enter untuk lanjut...";
        cin.get();
    }

    cout << "Program selesai. Sampai jumpa!" << endl;
    return 0;
}