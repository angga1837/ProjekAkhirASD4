#include "sistem.h"
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

// load data from file when program opened
SistemSeminar::SistemSeminar()
{
    daftar_seminar.push_back("Pengenalan YOLOv8 untuk Computer Vision");
    daftar_seminar.push_back("Workshop Penetration Testing Dasar");
    daftar_seminar.push_back("Sistem Embedded & IoT dengan ESP32");
    tm tm = {};
    tm.tm_year = 2026 - 1900;
    tm.tm_mon = 3;
    tm.tm_mday = 30;
    tm.tm_hour = 24;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    waktu_workshop = chrono::system_clock::from_time_t(std::mktime(&tm));
    muatData();
}

// save data to file when program is closed
SistemSeminar::~SistemSeminar()
{
    simpanData();
}

void SistemSeminar::jalankan()
{
    int mode;
    do
    {
        cout << "\n=============================================\n";
        cout << "         SISTEM REGISTRASI SEMINAR\n";
        cout << "=============================================\n";
        cout << "Login Sebagai:\n";
        cout << "1. User (Pendaftar)\n";
        cout << "2. Admin\n";
        cout << "0. Keluar Program\n";
        cout << "Pilih: ";
        cin >> mode;

        if (mode == 1)
            menuUser();
        else if (mode == 2)
            menuAdmin();

    } while (mode != 0);
    cout << "Menyimpan data... Terima kasih!\n";
}

void SistemSeminar::menuUser()
{
    int pilihan;
    do
    {
        cout << "\n=== MENU USER ===\n";
        cout << "1. Sign-Up (Daftar Seminar)\n";
        cout << "2. Log-In (Cek Dashboard)\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1)
        {
            Peserta p;
            cout << "\n--- FORM REGISTRASI ---\n";
            cout << "Nama Lengkap : ";
            getline(cin, p.nama);
            cout << "NIU          : ";
            getline(cin, p.NIU);
            cout << "Program Studi: ";
            getline(cin, p.prodi);
            cout << "Email        : ";
            getline(cin, p.email);
            cout << "No. Telp     : ";
            getline(cin, p.telp);

            char tambahLagi;
            do
            {
                cout << "\nPilihan Seminar Tersedia:\n";
                for (size_t i = 0; i < daftar_seminar.size(); i++)
                {
                    cout << i + 1 << ". " << daftar_seminar[i] << "\n";
                }
                int pilihSem;
                cout << "Masukkan pilihan seminar: ";
                cin >> pilihSem;
                cin.ignore();

                if (pilihSem > 0 && pilihSem <= (int)daftar_seminar.size())
                {
                    p.pilihan_seminar.push_back(daftar_seminar[pilihSem - 1]);
                    cout << ">> Seminar ditambahkan!\n";
                }
                cout << "Ingin daftar seminar lain? (y/n): ";
                cin >> tambahLagi;
                cin.ignore();
            } while (tambahLagi == 'y' || tambahLagi == 'Y');

            if (!p.pilihan_seminar.empty())
            {
                antrean.enqueue(p);
                cout << ">> Berhasil mendaftar! Silahkan menunggu verifikasi.\n";
            }
        }
        else if (pilihan == 2)
        {
            string loginNama, loginNIU;
            cout << "\n--- LOG IN ---\n";
            cout << "Masukkan Nama: ";
            getline(cin, loginNama);
            cout << "Masukkan NIU : ";
            getline(cin, loginNIU);

            Peserta userDitemukan;
            // check in queue
            if (antrean.cariPeserta(loginNama, loginNIU, userDitemukan))
            {
                cout << "\n=== DASHBOARD USER ===\n";
                cout << "Halo, " << userDitemukan.nama << "!\n";
                cout << "NIU   : " << userDitemukan.NIU << endl;
                cout << "Prodi : " << userDitemukan.prodi << endl;
                cout << "Email : " << userDitemukan.email << endl;
                cout << "No. HP: " << userDitemukan.telp << endl;
                cout << endl;
                cout << "Status: MENUNGGU VERIFIKASI\n";
                cout << "Harap ditunggu, pendaftaran Anda masih dalam proses verifikasi.\n";
                countdown();
            }
            // check in stack
            else if (riwayat.cariPeserta(loginNama, loginNIU, userDitemukan))
            {
                cout << "\n=== DASHBOARD USER ===\n";
                cout << "Halo, " << userDitemukan.nama << "!\n";
                cout << "NIU   : " << userDitemukan.NIU << endl;
                cout << "Prodi : " << userDitemukan.prodi << endl;
                cout << "Email : " << userDitemukan.email << endl;
                cout << "No. HP: " << userDitemukan.telp << endl;
                cout << endl;
                cout << "STATUS: TERVERIFIKASI\n";
                cout << "Selamat pendaftaran Anda telah diverifikasi!\n";
                countdown();
            }
            else
            {
                cout << "\n[!] Akun tidak ditemukan.\n";
            }
        }
    } while (pilihan != 0);
}

void SistemSeminar::menuAdmin()
{
    string inUser, inPass;
    cout << "\n--- LOGIN ADMIN ---\nUsername: ";
    cin >> inUser;
    cout << "Password: ";
    cin >> inPass;

    if (inUser != "admin" || inPass != "admin123")
    {
        cout << "Login gagal!\n";
        return;
    }

    int pilihan;
    do
    {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Lihat Antrean\n2. Verifikasi Peserta\n3. Lihat Riwayat\n4. Delete Peserta \n0. Log Out\nPilih: ";
        cin >> pilihan;

        if (pilihan == 1)
            antrean.tampilkan();
        else if (pilihan == 2)
        {
            Peserta diproses;
            if (antrean.dequeue(diproses))
            {
                riwayat.push(diproses);
                cout << ">> " << diproses.nama << " berhasil diverifikasi!\n";
            }
            else
                cout << "Antrean kosong.\n";
        }
        else if (pilihan == 3)
            riwayat.tampilkanSemua();
        else if (pilihan == 4) 
        {
            string niu;
            cout << "Masukkan NIU peserta yang ingin dihapus: ";
            cin >> niu;

            bool ditemukan = false;

            if (antrean.hapusByNIU(niu))
            {
                cout << ">> Peserta berhasil dihapus dari antrean.\n";
                ditemukan = true;
            }

            if (riwayat.hapusByNIU(niu))
            {
                cout << ">> Peserta berhasil dihapus dari riwayat.\n";
                ditemukan = true;
            }

            if (!ditemukan)
            {
                cout << ">> Peserta dengan NIU tersebut tidak ditemukan.\n";
            }
        }
    } while (pilihan != 0);
}

void SistemSeminar::simpanData()
{
    ofstream file("data_peserta.txt");
    if (!file.is_open())
        return;

    // save queue
    Node *tempQ = antrean.getFront();
    while (tempQ != nullptr)
    {
        file << "Q|" << tempQ->data.nama << "|" << tempQ->data.email << "|" << tempQ->data.telp << "|"
             << tempQ->data.NIU << "|" << tempQ->data.prodi << "|";
        for (const string &sem : tempQ->data.pilihan_seminar)
            file << sem << ",";
        file << "\n";
        tempQ = tempQ->next;
    }

    Node *tempS = riwayat.getTop();
    while (tempS != nullptr)
    {
        file << "S|" << tempS->data.nama << "|" << tempS->data.email << "|" << tempS->data.telp << "|"
             << tempS->data.NIU << "|" << tempS->data.prodi << "|";
        for (const string &sem : tempS->data.pilihan_seminar)
            file << sem << ",";
        file << "\n";
        tempS = tempS->next;
    }
    file.close();
}

void SistemSeminar::muatData()
{
    ifstream file("data_peserta.txt");
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string tipe, nama, email, telp, NIU, prodi, seminarList;

        getline(ss, tipe, '|');
        getline(ss, nama, '|');
        getline(ss, email, '|');
        getline(ss, telp, '|');
        getline(ss, NIU, '|');
        getline(ss, prodi, '|');
        getline(ss, seminarList, '|');

        Peserta p(nama, email, NIU, prodi, telp);
        stringstream ssSem(seminarList);
        string s;
        while (getline(ssSem, s, ','))
            if (!s.empty())
                p.pilihan_seminar.push_back(s);

        if (tipe == "Q")
            antrean.enqueue(p);
        else if (tipe == "S")
            riwayat.push(p);
    }
    file.close();
}

void SistemSeminar::countdown() {
    cout << "\n--- COUNTDOWN WORKSHOP ---\n";
    cout << "Tekan q lalu Enter untuk kembali ke menu utama.\n";

    while (true) {
        auto sekarang = chrono::system_clock::now();
        auto durasi = waktu_workshop - sekarang;

        if (durasi.count() <= 0) {
            cout << "Workshop sudah dimulai!\n";
            break;
        }

        long long total_detik = durasi.count() / 1000000000LL;  
        long long hari = total_detik / 86400;
        long long jam = (total_detik % 86400) / 3600;
        long long menit = (total_detik % 3600) / 60;
        long long detik = total_detik % 60;

        cout << "\rWaktu tersisa: " << hari << " hari, "
             << jam << " jam, "
             << menit << " menit, "
             << detik << " detik. ";
        cout.flush();

        if (cin.peek() == 'q') {
            cin.ignore();
            break;
        }

        for(int i = 0; i < 1000000000; i++) {}
    
    }

    cout << "\nKembali ke dashboard.\n";
}