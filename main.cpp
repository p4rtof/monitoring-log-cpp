#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Log {
  string id, waktu, level, sumber, pesan;
};

// 2 Struktur Data
vector<Log> listLog;                          // O(N) buat cari waktu dan sumber
unordered_map<string, vector<Log>> mapLevel;  // O(1) buat cari level dan error

// --- 1. BACA DATA DI FILE .TXT ---
void bacaDataFile() {
  ifstream file("data_log.txt");
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

    listLog.push_back(temp);
    mapLevel[temp.level].push_back(temp);
  }
  file.close();
}

// --- 2. INSERT LOG ---
void tambahLog() {
  Log baru;
  cout << "ID: ";
  cin >> baru.id;
  cin.ignore();
  cout << "Waktu (YYYY-MM-DD): ";
  getline(cin, baru.waktu);
  cout << "Level (INFO/ERROR/WARNING): ";
  getline(cin, baru.level);
  cout << "Sumber: ";
  getline(cin, baru.sumber);
  cout << "Pesan: ";
  getline(cin, baru.pesan);

  listLog.push_back(baru);
  mapLevel[baru.level].push_back(baru);

  ofstream file("data_log.txt", ios::app);
  file << baru.id << "|" << baru.waktu << "|" << baru.level << "|"
       << baru.sumber << "|" << baru.pesan << "\n";
  file.close();

  cout << "Log berhasil ditambah dan tersimpan permanen!\n";
}

// --- 3. SEARCH O(N) (VECTOR) ---
void cariWaktuAtauSumber(int pilihan, string keyword) {
  auto start = chrono::high_resolution_clock::now();
  int ketemu = 0;

  for (const auto& log : listLog) {
    if ((pilihan == 1 && log.waktu.find(keyword) != string::npos) ||
        (pilihan == 2 && log.sumber.find(keyword) != string::npos)) {
      cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber
           << " : " << log.pesan << "\n";
      ketemu++;
    }
  }

  auto end = chrono::high_resolution_clock::now();
  cout << "\nTotal ketemu: " << ketemu << " log.\n";
  cout << "Waktu pencarian Vector: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count()
       << " mikrodetik\n";
}

// --- 4. SEARCH O(1) (HASH TABLE) ---
void cariLevel(string target) {
  auto start = chrono::high_resolution_clock::now();

  auto it = mapLevel.find(target);
  auto end = chrono::high_resolution_clock::now();

  int ketemu = 0;

  if (it != mapLevel.end()) {
    for (const auto& log : it->second) {
      cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber
           << " : " << log.pesan << "\n";
    }
    ketemu = it->second.size();
  }

  cout << "\nTotal ketemu: " << ketemu << " log.\n";
  cout << "Waktu pencarian Hash Map: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count()
       << " mikrodetik\n";
}

// --- 5. STATISTIK ---
void tampilStatistik() {
  cout << "\n=== STATISTIK LOG ===\n";
  for (const auto& pair : mapLevel) {
    cout << "- " << pair.first << ": " << pair.second.size() << " LOG\n";
  }
  cout << "Total Keseluruhan: " << listLog.size() << " log\n";
}

// --- 6. HAPUS LOG ---
void hapusLogLama() {
  string batas;
  cout << "Hapus log SEBELUM tanggal (YYYY-MM-DD): ";
  cin >> batas;

  auto start = chrono::high_resolution_clock::now();

  vector<Log> logSisa;
  logSisa.reserve(listLog.size());
  mapLevel.clear();
  stringstream buffer;

  for (int i = 0; i < listLog.size(); i++) {
    if (listLog[i].waktu >= batas) {
      logSisa.push_back(listLog[i]);
      mapLevel[listLog[i].level].push_back(listLog[i]);
      buffer << listLog[i].id << "|" << listLog[i].waktu << "|"
             << listLog[i].level << "|" << listLog[i].sumber << "|"
             << listLog[i].pesan << "\n";
    }
  }
  listLog = logSisa;

  ofstream file("data_log.txt", ios::trunc);
  file << buffer.str();
  file.close();

  auto end = chrono::high_resolution_clock::now();
  cout << "\nSukses! Log terhapus permanen dari file .txt\n";
  cout << "Sisa log sekarang: " << listLog.size() << "\n";
  cout << "Waktu hapus & simpan: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count()
       << " mikrodetik\n";
}

int main() {
  bacaDataFile();
  int menu;

  while (true) {
    cout << "\n=== SISTEM MONITORING LOG (Total: " << listLog.size()
         << ") ===\n";
    cout << "1. Insert Log Baru\n";
    cout << "2. Cari Waktu (Vector)\n";
    cout << "3. Cari Sumber (Vector)\n";
    cout << "4. Cari Level (Hash Map)\n";
    cout << "5. Tampilkan Log ERROR\n";
    cout << "6. Hapus Log Lama\n";
    cout << "7. Statistik Log\n";
    cout << "8. Keluar\n";
    cout << "Pilih: ";
    cin >> menu;

    string kata;
    switch (menu) {
      case 1:
        tambahLog();
        break;
      case 2:
        cout << "Waktu: ";
        cin.ignore();
        getline(cin, kata);
        cariWaktuAtauSumber(1, kata);
        break;
      case 3:
        cout << "Sumber: ";
        cin.ignore();
        getline(cin, kata);
        cariWaktuAtauSumber(2, kata);
        break;
      case 4:
        cout << "Level (INFO/WARNING/ERROR): ";
        cin >> kata;
        for (char& c : kata) {
          c = toupper(c);
        }
        cariLevel(kata);
        break;
      case 5:
        cout << "\n--- LOG ERROR ---\n";
        cariLevel("ERROR");
        break;
      case 6:
        hapusLogLama();
        break;
      case 7:
        tampilStatistik();
        break;
      case 8:
        cout << "\nProgram selesai!\n";
        return 0;
      default:
        cout << "Menu salah!\n";
    }
  }
}