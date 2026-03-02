#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

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
        temp.timestamp = "2026-03-02 23:50:00"; // Bisa dikembangkan pakai library time
        temp.level = levels[rand() % 3];        // Acak level
        temp.source = sources[rand() % 4];      // Acak sumber modul
        temp.message = "Aktivitas sistem nomor " + to_string(i);
        
        container.push_back(temp);
    }
    cout << "Berhasil membuat " << jumlah << " data log dummy." << endl;
}

int main() {
    vector<Log> gudangLog;
    
    // Contoh menjalankan tugas orang 1
    generateDummyData(gudangLog, 10); 
    
    return 0;
}