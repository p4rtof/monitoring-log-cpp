#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <chrono>

using namespace std;

struct Log{
    string id, waktu, level, sumber, pesan;
};

vector<Log> listLog;
unordered_map<string, vector<Log>> mapLevel;

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

void cariPakaiHashTable(string targetLevel){
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

void cariLog(int pilihan, string keyword){
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

int main(){
    bacaDataFile("data_log.txt");

    int menu;
    while (true){
        cout << "\n=== MENU LOG SYSTEM (Total: " << listLog.size() << " data) ===\n";
        cout << "1. Tambah Log\n2. Cari Waktu\n3. Cari Level\n4. Cari Sumber\n5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        if (menu == 5){
            cout << "Program selesai!\n";
            break;
        }
        if (menu == 1){
            tambahLog();
        }
        else if (menu == 3){
            string cari;
            cout << "Masukkan Level (INFO/WARNING/ERROR): ";
            cin >> cari;
            cariPakaiHashTable(cari);
        }
        else if (menu == 2 || menu == 4){
            string cari;
            cout << "Masukkan kata kunci: ";

            cin.ignore(); 
            getline(cin, cari); 

            if (menu == 2)
                cariLog(1, cari);
            if (menu == 4)
                cariLog(3, cari);
        }
        else{
            cout << "\nMenu Tidak Tersedia\n";
        }
    }

    return 0;
}