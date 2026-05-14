#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <ctime>

using namespace std;

// =====================================================
// SISTEM MONITORING & LOG AKTIVITAS APLIKASI
// Struktur Data: vector (O(N)) + unordered_map (O(1))
// =====================================================

struct Log {
  string id, waktu, level, sumber, pesan;
};

const string FILE_LOG = "data_log.txt";

// --- 2 STRUKTUR DATA UTAMA ---
vector<Log> listLog;                         // Linear search: waktu & sumber
unordered_map<string, vector<Log>> mapLevel; // Hash lookup: level & error

string toLower(string s) {
  for (char& c : s) c = tolower(c);
  return s;
}

string waktuSekarang() {
  time_t now = time(nullptr);
  tm* t = localtime(&now);
  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
  return string(buf);
}

void tampilLog(const Log& log) {
  cout << "[" << log.waktu << "] " << log.level
       << " | " << log.sumber << " : " << log.pesan << "\n";
}

// =====================================================
// 1. BACA DATA DARI FILE
// =====================================================
void bacaDataFile() {
  ifstream file(FILE_LOG);
  if (!file.is_open()) {
    cout << "[INFO] File '" << FILE_LOG << "' tidak ditemukan. Mulai dengan data kosong.\n";
    return;
  }

  string line;
  int baris = 0;
  while (getline(file, line)) {
    if (line.empty()) continue;
    stringstream ss(line);
    Log temp;

    getline(ss, temp.id,     '|');
    getline(ss, temp.waktu,  '|');
    getline(ss, temp.level,  '|');
    getline(ss, temp.sumber, '|');
    getline(ss, temp.pesan,  '|');

    // Validasi field tidak kosong
    if (temp.id.empty() || temp.waktu.empty() || temp.level.empty()) continue;

    listLog.push_back(temp);
    mapLevel[temp.level].push_back(temp);
    baris++;
  }
  file.close();
  cout << "[INFO] " << baris << " log berhasil dimuat dari " << FILE_LOG << "\n";
}

// =====================================================
// 2. INSERT LOG BARU
// =====================================================
void tambahLog() {
  Log baru;

  cout << "ID\t\t: ";
  cin >> baru.id;
  cin.ignore();

  baru.waktu = waktuSekarang();
  cout << "Waktu\t\t: " << baru.waktu << " (otomatis)\n";

  cout << "Level (INFO/WARNING/ERROR) : ";
  getline(cin, baru.level);
  for (char& c : baru.level) c = toupper(c);  

  cout << "Sumber\t\t: ";
  getline(cin, baru.sumber);

  cout << "Pesan\t\t: ";
  getline(cin, baru.pesan);

  auto start = chrono::high_resolution_clock::now();

  listLog.push_back(baru);
  mapLevel[baru.level].push_back(baru);

  ofstream file(FILE_LOG, ios::app);
  file << baru.id    << "|" << baru.waktu  << "|"
       << baru.level << "|" << baru.sumber << "|"
       << baru.pesan << "\n";
  file.close();

  auto end = chrono::high_resolution_clock::now();
  cout << "\nLog berhasil ditambah dan tersimpan permanen!\n";
  cout << "Waktu insert: "
       << chrono::duration_cast<chrono::microseconds>(end - start).count()
       << " mikrodetik\n";
}

// =====================================================
// 3. SEARCH O(N) — VECTOR (Waktu & Sumber)
// =====================================================
void cariWaktuAtauSumber(int pilihan, string keyword) {
  auto start = chrono::high_resolution_clock::now();
  int ketemu = 0;

  string kwLower = toLower(keyword);

  for (const auto& log : listLog) {
    string target = toLower(pilihan == 1 ? log.waktu : log.sumber);
    if (target.find(kwLower) != string::npos) {
      tampilLog(log);
      ketemu++;
    }
  }

  auto end = chrono::high_resolution_clock::now();
  long long us = chrono::duration_cast<chrono::microseconds>(end - start).count();

  cout << "\nTotal ditemukan : " << ketemu << " log\n";
  cout << "Struktur data   : Vector (Linear Search)\n";
  cout << "Kompleksitas    : O(N)  N=" << listLog.size() << "\n";
  cout << "Waktu eksekusi  : " << us << " mikrodetik\n";
}

// =====================================================
// 4. SEARCH O(1) — HASH MAP (Level)
// =====================================================
void cariLevel(string target) {
  for (char& c : target) c = toupper(c);

  auto start = chrono::high_resolution_clock::now();
  auto it = mapLevel.find(target);
  auto end = chrono::high_resolution_clock::now();
  long long us = chrono::duration_cast<chrono::microseconds>(end - start).count();

  int ketemu = 0;
  if (it != mapLevel.end()) {
    for (const auto& log : it->second) tampilLog(log);
    ketemu = it->second.size();
  }

  cout << "\nTotal ditemukan : " << ketemu << " log\n";
  cout << "Struktur data   : Hash Map (Direct Lookup)\n";
  cout << "Kompleksitas    : O(1) average\n";
  cout << "Waktu eksekusi  : " << us << " mikrodetik\n";
}

// =====================================================
// 5. STATISTIK LOG
// =====================================================
void tampilStatistik() {
  cout << "\n=== STATISTIK LOG ===\n";

  size_t memVector = listLog.size() * sizeof(Log);
  size_t memMap = 0;
  for (const auto& pair : mapLevel) {
    memMap += pair.second.size() * sizeof(Log);
    memMap += pair.first.size();
  }

  for (const auto& pair : mapLevel) {
    double pct = listLog.empty() ? 0 : (100.0 * pair.second.size() / listLog.size());
    cout << "  " << pair.first << " : " << pair.second.size()
         << " log (" << fixed;
    cout.precision(1);
    cout << pct << "%)\n";
  }
  cout << "  Total          : " << listLog.size() << " log\n";
  cout << "\n--- Estimasi Memori ---\n";
  cout << "  Vector         : ~" << memVector / 1024 << " KB\n";
  cout << "  Hash Map       : ~" << memMap / 1024 << " KB (overhead index)\n";
}

// =====================================================
// 6. HAPUS LOG LAMA (by tanggal)
// =====================================================
void hapusLogLama() {
  string batas;
  cout << "Hapus log SEBELUM tanggal (YYYY-MM-DD): ";
  cin >> batas;

  int sebelum = listLog.size();
  auto start = chrono::high_resolution_clock::now();

  vector<Log> logSisa;
  logSisa.reserve(listLog.size());
  mapLevel.clear();
  stringstream buffer;

  for (const auto& log : listLog) {
    if (log.waktu.substr(0, 10) >= batas) {
      logSisa.push_back(log);
      mapLevel[log.level].push_back(log);
      buffer << log.id    << "|" << log.waktu  << "|"
             << log.level << "|" << log.sumber << "|"
             << log.pesan << "\n";
    }
  }
  listLog = logSisa;

  ofstream file(FILE_LOG, ios::trunc);
  file << buffer.str();
  file.close();

  auto end = chrono::high_resolution_clock::now();
  long long us = chrono::duration_cast<chrono::microseconds>(end - start).count();

  int terhapus = sebelum - (int)listLog.size();
  cout << "\nSukses! " << terhapus << " log dihapus permanen\n";
  cout << "Sisa log      : " << listLog.size() << "\n";
  cout << "Waktu proses  : " << us << " mikrodetik\n";
}

// =====================================================
// MAIN MENU
// =====================================================
int main() {
  cout << "======================================\n";
  cout << "  SISTEM MONITORING & LOG AKTIVITAS  \n";
  cout << "  Kelompok 4.9 - Struktur Data         \n";
  cout << "======================================\n\n";

  bacaDataFile();

  int menu;
  while (true) {
    cout << "\n=== MENU (Total Log: " << listLog.size() << ") ===\n";
    cout << "  1. Insert Log Baru\n";
    cout << "  2. Cari berdasarkan Waktu  [Vector O(N)]\n";
    cout << "  3. Cari berdasarkan Sumber [Vector O(N)]\n";
    cout << "  4. Cari berdasarkan Level  [Hash Map O(1)]\n";
    cout << "  5. Tampilkan Log ERROR     [Hash Map O(1)]\n";
    cout << "  6. Hapus Log Lama\n";
    cout << "  7. Statistik & Memori\n";
    cout << "  8. Keluar\n";
    cout << "Pilih: ";
    cin >> menu;

    string kata;
    switch (menu) {
      case 1:
        tambahLog();
        break;
      case 2:
        cout << "Cari waktu (format: YYYY-MM-DD): ";
        cin.ignore();
        getline(cin, kata);
        cariWaktuAtauSumber(1, kata);
        break;
      case 3:
        cout << "Cari sumber : ";
        cin.ignore();
        getline(cin, kata);
        cariWaktuAtauSumber(2, kata);
        break;
      case 4:
        cout << "Level (INFO/WARNING/ERROR): ";
        cin >> kata;
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
        cout << "\nProgram selesai. Terima kasih!\n";
        return 0;
      default:
        cout << "Menu tidak valid! Pilih 1-8.\n";
    }
  }
}