#include <iostream>
#include <vector>
#include <fstream> // buat menulis, membaca di file .txt
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

struct Log
{
    string id, waktu, level, sumber, pesan;
};

void bacaDataFile(vector<Log> &logs, string filename)
{
    ifstream file(filename);
    if (!file.is_open())
        return; // jika file tidak ada/tidak bisa kebuka maka keluar dari fungsi

    logs.clear(); // memastikan vector yang dibuat kosong
    string line;
    while (getline(file, line))
    { // baca semua baris sampai EOF (di ujung file)
        if (line.empty())
            continue;              // jika ada baris kosong, maka lewatin ke baris selanjutnya
        stringstream ss(line);     // memotong 1 baris menjadi beberapa bagian
        Log temp;                  // simpan data sementara
        getline(ss, temp.id, '|'); // memasukkan data ke 'id' sampai ketemu '|'
        getline(ss, temp.waktu, '|');
        getline(ss, temp.level, '|');
        getline(ss, temp.sumber, '|');
        getline(ss, temp.pesan, '|');
        logs.push_back(temp); // masukin data ke vektor
    }
    file.close(); // file di tutup
}

void addLogManual(vector<Log> &logs, string filename)
{
    Log newLog;
    cout << "\n--- Tambah Log Baru ---" << endl;
    cout << "ID: ";
    cin >> newLog.id;
    cin.ignore();
    cout << "Waktu (YYYY-MM-DD HH:MM:SS): ";
    getline(cin, newLog.waktu);
    cout << "Level (INFO/WARNING/ERROR): ";
    getline(cin, newLog.level);
    cout << "Sumber: ";
    getline(cin, newLog.sumber);
    cout << "Pesan: ";
    getline(cin, newLog.pesan);

    logs.push_back(newLog); // Simpan ke memori

    // Menambah ke baris paling bawah file (ios::app)
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << newLog.id << "|" << newLog.waktu << "|" << newLog.level << "|"
             << newLog.sumber << "|" << newLog.pesan << endl;
        file.close();
        cout << "Berhasil! Data lama tetap aman & data baru tersimpan." << endl;
    }
}

string toLower(string s) {
    for (char &c : s) c = tolower(c); // tolower ini bawaan C++
    return s;
}

// --- ORANG 3: Fungsi Cari (Search) ---
void searchLog(const vector<Log>& logs, string kriteria, int tipe) {
    bool found = false;
    kriteria = toLower(kriteria);
    cout << "\n--- Hasil Pencarian ---\n";

    for (const auto& log : logs) {
        bool match = false;

        switch (tipe) {
            case 1: match = (toLower(log.waktu).find(kriteria) != string::npos); break; // Cari waktu
            case 2: match = (toLower(log.level) == kriteria); break;                    // Cari level
            case 3: match = (toLower(log.sumber) == kriteria); break;                   // Cari sumber
        }

        if (match) {
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << '\n';
            found = true;
        }
    }

    if (!found) cout << "Data tidak ditemukan.\n";
}

int main()
{
    vector<Log> listLog;
    string fileData = "data_log.txt";

    // OTOMATIS LOAD DATA LAMA
    bacaDataFile(listLog, fileData);

    int pil;
    while (true)
    {
        cout << "\n=== MONITORING LOG SYSTEM (Ready: " << listLog.size() << " data) ===" << endl;
        cout << "1. Cari Waktu\n2. Cari Level\n3. Cari Sumber\n4. Tambah Data Baru\n5. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pil;

        if (pil == 5)
            break;
        if (pil == 4)
        {
            addLogManual(listLog, fileData);
        }
        else
        {
            string key;
            cout << "Masukkan Kata Kunci: ";
            cin.ignore();
            getline(cin, key);
            searchLog(listLog, key, pil);
        }
    }
    return 0;
}