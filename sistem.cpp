#include "sistem.h"
#include <bits/stdc++.h>

using namespace std;

SistemSeminar::SistemSeminar() {
    daftar_seminar.push_back("Pengenalan YOLOv8 untuk Computer Vision");
    daftar_seminar.push_back("Workshop Penetration Testing Dasar");
    daftar_seminar.push_back("Sistem Embedded & IoT dengan ESP32");
}

SistemSeminar::~SistemSeminar() {
}

void SistemSeminar::jalankan() {
    int mode;
    do {
        cout << "\n=============================================\n";
        cout << "  SISTEM REGISTRASI SEMINAR\n";
        cout << "=============================================\n";
        cout << "Login Sebagai:\n";
        cout << "1. User (Pendaftar)\n";
        cout << "2. Admin\n";
        cout << "0. Keluar Program\n";
        cout << "Pilih: ";
        cin >> mode;

        if (mode == 1) menuUser();
        else if (mode == 2) menuAdmin();
        
    } while (mode != 0);
    cout << "Menyimpan data... Terima kasih telah menggunakan program ini.\n";
}

void SistemSeminar::menuUser() {
    int pilihan;
    do {
        cout << "\n=== MENU USER ===\n";
        cout << "1. Sign-Up (Daftar Seminar)\n";
        cout << "2. Log-In (Cek Dashboard)\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            Peserta p;
            cout << "\n--- FORM REGISTRASI ---\n";
            cout << "Nama Lengkap : "; getline(cin, p.nama);
            cout << "NIM          : "; getline(cin, p.NIM);
            cout << "Program Studi: "; getline(cin, p.prodi);
            cout << "Email        : "; getline(cin, p.email);
            cout << "No. Telp     : "; getline(cin, p.telp);
            
            char tambahLagi;
            do {
                cout << "\nPilihan Seminar Tersedia:\n";
                for (size_t i = 0; i < daftar_seminar.size(); i++) {
                    cout << i + 1 << ". " << daftar_seminar[i] << "\n";
                }
                int pilihSem;
                cout << "Masukkan nomor seminar: ";
                cin >> pilihSem;
                cin.ignore();

                if (pilihSem > 0 && pilihSem <= (int)daftar_seminar.size()) {
                    p.pilihan_seminar.push_back(daftar_seminar[pilihSem - 1]);
                    cout << ">> Seminar ditambahkan!\n";
                } else {
                    cout << ">> Pilihan tidak valid!\n";
                }

                cout << "Ingin daftar seminar lain? (y/n): ";
                cin >> tambahLagi;
                cin.ignore();
            } while (tambahLagi == 'y' || tambahLagi == 'Y');

            if (!p.pilihan_seminar.empty()) {
                antrean.enqueue(p);
                cout << ">> Berhasil mendaftar! Anda masuk dalam antrean registrasi.\n";
            } else {
                cout << ">> Anda belum memilih seminar apa pun. Registrasi dibatalkan.\n";
            }

        } else if (pilihan == 2) {
            string loginNama, loginNIM;
            cout << "\n--- LOG IN ---\n";
            cout << "Masukkan Nama: "; getline(cin, loginNama);
            cout << "Masukkan NIM : "; getline(cin, loginNIM);

            Peserta userDitemukan;
            if (antrean.cariPeserta(loginNama, loginNIM, userDitemukan)) {
                cout << "\n=== DASHBOARD USER ===\n";
                cout << "Halo, " << userDitemukan.nama << "!\n";
                cout << "Seminar Terdaftar:\n";
                for (const string& sem : userDitemukan.pilihan_seminar) {
                    cout << "- " << sem << "\n";
                }
                cout << "Status   : Menunggu verifikasi (Masih dalam antrean)\n";
                cout << "NIM      : " << userDitemukan.NIM << endl;
                cout << "No. Telp : " << userDitemukan.telp << endl;
            } else {
                cout << "Akun tidak ditemukan di antrean (atau sudah diverifikasi).\n";
            }
        }
    } while (pilihan != 0);
}

void SistemSeminar::menuAdmin() {
    string inUser, inPass;
    cout << "\n--- LOGIN ADMINM ---\n";
    cout << "Username: "; cin >> inUser;
    cout << "Password: "; cin >> inPass;

    if (inUser != "admin" || inPass != "admin123") {
        cout << "Login gagal!\n";
        return;
    }

    int pilihan;
    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Lihat Antrean Peserta\n";
        cout << "2. Proses Antrean (Verifikasi)\n";
        cout << "3. Lihat Riwayat (Peserta Diverifikasi)\n";
        cout << "4. Kelola Opsi Seminar\n";
        cout << "0. Log Out\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: antrean.tampilkan(); break;
            case 2: {
                Peserta diproses;
                if (antrean.dequeue(diproses)) {
                    riwayat.push(diproses);
                    cout << ">> Peserta " << diproses.nama << " berhasil diverifikasi!\n";
                } else {
                    cout << "Antrean registrasi kosong.\n";
                }
                break;
            }
            case 3: 
                riwayat.tampilkanTerakhir();
                riwayat.tampilkanSemua(); 
                break;
            case 4: {
                cout << "\n--- KELOLA SEMINAR ---\n";
                for (size_t i = 0; i < daftar_seminar.size(); i++) {
                    cout << i + 1 << ". " << daftar_seminar[i] << "\n";
                }
                cout << "Ketik nama seminar baru untuk ditambah: ";
                string semBaru;
                getline(cin, semBaru);
                daftar_seminar.push_back(semBaru);
                cout << ">> Seminar berhasil ditambahkan.\n";
                break;
            }
        }
    } while (pilihan != 0);
}

