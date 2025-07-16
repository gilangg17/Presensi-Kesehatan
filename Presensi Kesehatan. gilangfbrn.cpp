#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>

using namespace std;

map<string, string> akun = {
    {"dokter", "123"},
    {"perawat", "456"}
};

string waktuSekarang() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

bool login(string username, string password) {
    return akun.find(username) != akun.end() && akun[username] == password;
}

void presensi(string username, string tipe) {
    ofstream file("data_presensi.txt", ios::app);
    file << username << "," << tipe << "," << waktuSekarang();
    file.close();
    cout << "Presensi " << tipe << " berhasil dicatat.\n";
}

void tampilkanRekap() {
    ifstream file("data_presensi.txt");
    string baris;
    cout << "\n=== Rekap Presensi ===\n";
    while (getline(file, baris)) {
        cout << baris;
    }
    file.close();
    cout << "\n======================\n";
}

int main() {
    string username, password;
    cout << "==== Login Tenaga Kesehatan ====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (login(username, password)) {
        int pilihan;
        do {
            cout << "\nMenu:\n1. Check-in\n2. Check-out\n3. Tampilkan Rekap\n4. Keluar\nPilih: ";
            cin >> pilihan;
            switch (pilihan) {
                case 1:
                    presensi(username, "Check-in");
                    break;
                case 2:
                    presensi(username, "Check-out");
                    break;
                case 3:
                    tampilkanRekap();
                    break;
                case 4:
                    cout << "Keluar dari sistem.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 4);
    } else {
        cout << "Login gagal. Coba lagi.\n";
    }

    return 0;
}
