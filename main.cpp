#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include <algorithm>

using namespace std;

struct Log{
    string id, waktu, level, sumber, pesan;
};

vector<Log> listLog;
map<string, vector<Log>> mapLevel;

void bacaDataFile(string filename){
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)){ 
        if (line.empty())
            continue;
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

// cari pake HashTable -> LEVEL
void cariLevel(string targetLevel){
    auto start = chrono::high_resolution_clock::now();

    auto it = mapLevel.find(targetLevel);
    bool ketemu = (it != mapLevel.end() && !it->second.empty());

    auto end = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "\n--- Hasil Pencarian Level: " << targetLevel << " ---\n";
    if (ketemu){
        for (const auto &log : it->second){
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << "\n";
        }
        cout << "\nTotal data ketemu: " << it->second.size() << " log.\n";
    }
    else{
        cout << "Data Tidak Sesuai (Kapital)\n";
    }

    cout << "Waktu murni pencarian Hash Table: " << durasi << " mikrodetik\n";
}

void tambahLog(){
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
    file << baru.id << "|" << baru.waktu << "|" << baru.level << "|" << baru.sumber << "|" << baru.pesan << "\n";
    cout << "Log berhasil tersimpan!\n";
}

void cariWaktuDanSumber(int pilihan, string keyword){
    vector<Log> hasilCari;

    auto start = chrono::high_resolution_clock::now();

    for (const auto &log : listLog){
        bool cocok = false;
        if (pilihan == 1 && log.waktu.find(keyword) != string::npos)
            cocok = true;
        else if (pilihan == 3 && log.sumber.find(keyword) != string::npos)
            cocok = true;
        if (cocok){
            hasilCari.push_back(log);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "\n--- Hasil Pencarian ---\n";
    if (!hasilCari.empty()){
        for (const auto &log : hasilCari){
            cout << "[" << log.waktu << "] " << log.level << " | " << log.sumber << " : " << log.pesan << "\n";
        }
        cout << "\nTotal data ketemu: " << hasilCari.size() << " log.\n";
    }
    else{
        cout << "Log Tidak Ditemukan!\n";
    }
    cout << "Waktu murni pencarian Vector: " << durasi << " mikrodetik\n";
}

void hapusLogLama() {
    string batasWaktu;
    cout << "Hapus log SEBELUM tanggal (YYYY-MM-DD): ";
    cin >> batasWaktu;

    cout << "\nPilih Metode Penghapusan:\n";
    cout << "--------------------------\n";
    cout << "1. Langsung hapus di .txt \n";
    cout << "2. Hapus di RAM dan simpan saat exit \n";
    cout << "Pilih (1/2): ";
    int opsi;
    cin >> opsi;

    auto start = chrono::high_resolution_clock::now();

    // 1. Pindahin log yang masih aman
    vector<Log> logSisa;
    for (int i = 0; i < listLog.size(); i++) {
        if (listLog[i].waktu >= batasWaktu) { 
            logSisa.push_back(listLog[i]); 
        }
    }
    listLog = logSisa; 

    // 2. Kosongin map dan isi ulang
    mapLevel.clear();
    for (int i = 0; i < listLog.size(); i++) {
        mapLevel[listLog[i].level].push_back(listLog[i]);
    }

    // 3. Eksekusi sesuai opsi
    if (opsi == 1) {
        // Tulis langsung ke file saat itu juga
        stringstream buffer;
        for (int i = 0; i < listLog.size(); i++) {
            buffer << listLog[i].id << "|" << listLog[i].waktu << "|" << listLog[i].level << "|" 
                   << listLog[i].sumber << "|" << listLog[i].pesan << "\n";
        }
        ofstream file("data_log.txt", ios::trunc); 
        file << buffer.str(); 
        file.close();
    }

    auto end = chrono::high_resolution_clock::now();
    auto durasi = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "\nSukses! Sisa total log sekarang: " << listLog.size() << "\n";
    cout << "Waktu murni hapus & sinkronisasi: " << durasi << " mikrodetik\n";
}

void simpanKeFile() {
    stringstream buffer;
    for (int i = 0; i < listLog.size(); i++) {
        buffer << listLog[i].id << "|" << listLog[i].waktu << "|" << listLog[i].level << "|" 
               << listLog[i].sumber << "|" << listLog[i].pesan << "\n";
    }
    
    ofstream file("data_log.txt", ios::trunc); // Langsung simpan ke .txt
    file << buffer.str(); 
    file.close();
}


int main(){
    bacaDataFile("data_log.txt");

    int menu;
    while (true){
        cout << "\n=== MENU LOG SYSTEM (Total: " << listLog.size() << " data) ===\n";
        cout << "1. Tambah Log\n2. Cari Waktu\n3. Cari Level\n4. Cari Sumber\n5. Hapus Log Lama\n6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        switch (menu) {
            case 1:
                tambahLog();
                break;
                
            case 2:
            case 4: { // Pakai kurung kurawal karena ada deklarasi variabel baru
                string cari;
                cout << "Masukkan kata kunci: ";
                cin.ignore(); 
                getline(cin, cari); 

                if (menu == 2)
                    cariWaktuDanSumber(1, cari);
                else 
                    cariWaktuDanSumber(3, cari);
                break;
            }
            
            case 3: { // Pakai kurung kurawal juga di sini
                string cari;
                cout << "Masukkan Level (INFO/WARNING/ERROR): ";
                cin >> cari;
                cariLevel(cari);
                break;
            }
            
            case 5:
                hapusLogLama(); // Fungsi yang baru kita buat
                break;
                
            case 6:
                cout << "\nMenyimpan data...\n";
                simpanKeFile();
                cout << "Program selesai!\n";
                return 0; // Pakai return 0 biar langsung keluar dari program, bukan break
                
            default:
                cout << "\nMenu Tidak Tersedia\n";
                break;
        }
    }

    return 0;
}