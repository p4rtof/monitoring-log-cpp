#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Domain Data (Minimal)
struct Log {
    int id;
    string timestamp; // Format: YYYY-MM-DD HH:MM:SS
    string level;     // INFO, WARNING, ERROR
    string source;    // Auth, Payment, Inventory
    string message;
};

// Implementasi Struktur Data 1: Vector (Dynamic Array)
vector<Log> logSystem;

void insertLog(int id, string time, string lvl, string src, string msg) {
    logSystem.push_back({id, time, lvl, src, msg});
}

void searchByLevel(string lvl) {
    cout << "--- Hasil Pencarian Level: " << lvl << " ---" << endl;
    for (const auto& l : logSystem) {
        if (l.level == lvl) {
            cout << "[" << l.timestamp << "] " << l.source << ": " << l.message << endl;
        }
    }
}

int main() {
    // Simulasi Insert (Bisa dipindah ke fungsi generator dummy)
    insertLog(1, "2026-03-02 10:00:01", "INFO", "Auth", "User Fadhla Login");
    insertLog(2, "2026-03-02 10:05:20", "ERROR", "Database", "Connection Timeout");

    // Pengujian Awal Search
    auto start = chrono::high_resolution_clock::now();
    
    searchByLevel("ERROR");
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    
    cout << "\nWaktu pencarian: " << elapsed.count() << " detik" << endl;

    return 0;
}