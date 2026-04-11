#include "sistem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

// Format time_point ke string yang mudah dibaca
static string formatWaktu(const chrono::system_clock::time_point &tp)
{
    time_t t = chrono::system_clock::to_time_t(tp);
    tm *ltm = localtime(&t);
    char buf[32];
    strftime(buf, sizeof(buf), "%d %B %Y, %H:%M", ltm);
    return string(buf);
}

//  Isi seminar bawaan + muat data (constructor)
SistemSeminar::SistemSeminar()
{
    // Seminar bawaan dengan detail lengkap
    // Format waktu_str: "YYYY-MM-DD HH:MM"
    daftar_seminar.push_back(InfoSeminar(
        "Pengenalan YOLOv8 untuk Computer Vision",
        "Gedung TI Lantai 3 - Lab Komputer A",
        "Dr. Andi Pratama, M.Kom.",
        "2026-04-30 09:00"));
    daftar_seminar.push_back(InfoSeminar(
        "Workshop Penetration Testing Dasar",
        "Gedung TI Lantai 2 - Lab Jaringan",
        "Rizky Firmansyah, CEH",
        "2026-05-07 13:00"));
    daftar_seminar.push_back(InfoSeminar(
        "Sistem Embedded & IoT dengan ESP32",
        "Gedung Elektro - Lab Embedded System",
        "Prof. Budi Santoso, Ph.D.",
        "2026-05-14 10:00"));

    muatData();
}

//  Destructor
SistemSeminar::~SistemSeminar()
{
    simpanData();
}

//  Cari InfoSeminar berdasarkan nama
bool SistemSeminar::cariInfoSeminar(const string &nama, InfoSeminar &out) const
{
    for (const auto &s : daftar_seminar)
    {
        if (s.nama == nama)
        {
            out = s;
            return true;
        }
    }
    return false;
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

        clearline();
        clearline();
        clearline();
        clearline();
        clearline();

        if (mode == 1)
            menuUser();
        else if (mode == 2)
            menuAdmin();

    } while (mode != 0);
    cout << "\nMenyimpan data... Terima kasih!\n";
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

        clearline();
        clearline();
        clearline();
        clearline();

        // daftar/signin
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
                cout << "\n--- PILIHAN SEMINAR TERSEDIA ---\n";

                for (size_t i = 0; i < daftar_seminar.size(); i++)
                {
                    const InfoSeminar &s = daftar_seminar[i];
                    cout << i + 1 << ". " << s.nama << "\n";
                    cout << "   Tempat  : " << s.tempat << "\n";
                    cout << "   Pengisi : " << s.pengisi << "\n";
                    cout << "   Jadwal  : " << formatWaktu(s.waktu);
                    if (s.sudahLewat())
                        cout << "  [SUDAH LEWAT]";
                    cout << "\n";
                }

                int pilihSem;
                cout << "Masukkan pilihan seminar (0 untuk batal): ";
                cin >> pilihSem;
                cin.ignore();

                clearline();
                clearline();
                clearline();
                clearline();
                for (size_t i = 0; i < daftar_seminar.size(); i++)
                {
                    clearline();
                    clearline();
                    clearline();
                    clearline();
                }

                if (pilihSem == 0)
                {
                    break;
                }
                else if (pilihSem > 0 && pilihSem <= (int)daftar_seminar.size())
                {
                    const InfoSeminar &dipilih = daftar_seminar[pilihSem - 1];

                    if (dipilih.sudahLewat())
                    {
                        cout << "\n[!] Pendaftaran ditolak!\n";
                        cout << "    Seminar \"" << dipilih.nama << "\" sudah lewat batas waktunya\n";
                        cout << "    (Jadwal: " << formatWaktu(dipilih.waktu) << ").\n";
                        pressEnterToContinue();
                        clearline();
                        clearline();
                        clearline();
                        clearline();
                        clearline();
                    }
                    else
                    {
                        bool sudahDipilih = false;
                        for (const auto &ns : p.pilihan_seminar)
                            if (ns == dipilih.nama)
                            {
                                sudahDipilih = true;
                                break;
                            }

                        if (sudahDipilih)
                        {
                            cout << "\n[!] Anda sudah memilih seminar ini sebelumnya.\n";
                            pressEnterToContinue();
                            clearline();
                            clearline();
                            clearline();
                        }
                        else
                        {
                            p.pilihan_seminar.push_back(dipilih.nama);
                            cout << "\n>> Seminar \"" << dipilih.nama << "\" ditambahkan!\n";
                        }
                    }
                }
                else
                {
                    cout << "\n[!] Pilihan tidak valid.\n";
                }

                cout << "\nIngin daftar seminar lain? (y/n): ";
                cin >> tambahLagi;
                cin.ignore();
                clearline();
                clearline();

            } while (tambahLagi == 'y' || tambahLagi == 'Y');

            if (!p.pilihan_seminar.empty())
            {
                antrean.enqueue(p);
                cout << "\n>> Berhasil mendaftar! Silahkan menunggu verifikasi.\n";
                pressEnterToContinue();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
            }
            else
            {
                cout << "\n[!] Tidak ada seminar yang dipilih. Pendaftaran dibatalkan.\n";
                pressEnterToContinue();
                clearline();
                clearline();
                clearline();
            }
        }
        // Masuk log in
        else if (pilihan == 2)
        {
            string loginNama, loginNIU;
            cout << "\n--- LOG IN ---\n";
            cout << "Masukkan Nama: ";
            getline(cin, loginNama);
            cout << "Masukkan NIU : ";
            getline(cin, loginNIU);

            clearline();
            clearline();
            clearline();
            clearline();
            clearline();
            clearline();

            Peserta userDitemukan;

            if (antrean.cariPeserta(loginNama, loginNIU, userDitemukan))
            {
                cout << "\n=== DASHBOARD USER ===\n";
                cout << "Halo, " << userDitemukan.nama << "!\n";
                cout << "NIU   : " << userDitemukan.NIU << "\n";
                cout << "Prodi : " << userDitemukan.prodi << "\n";
                cout << "Email : " << userDitemukan.email << "\n";
                cout << "No. HP: " << userDitemukan.telp << "\n\n";
                cout << "Status: MENUNGGU VERIFIKASI\n";
                cout << "Harap ditunggu, pendaftaran Anda masih dalam proses verifikasi.\n";
                countdownSeminar(userDitemukan);
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
            }
            else if (riwayat.cariPeserta(loginNama, loginNIU, userDitemukan))
            {
                cout << "\n=== DASHBOARD USER ===\n";
                cout << "Halo, " << userDitemukan.nama << "!\n";
                cout << "NIU   : " << userDitemukan.NIU << "\n";
                cout << "Prodi : " << userDitemukan.prodi << "\n";
                cout << "Email : " << userDitemukan.email << "\n";
                cout << "No. HP: " << userDitemukan.telp << "\n\n";
                cout << "STATUS: TERVERIFIKASI\n";
                cout << "Selamat, pendaftaran Anda telah diverifikasi!\n";
                countdownSeminar(userDitemukan);
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
            }
            else
            {
                cout << "\n[!] Akun tidak ditemukan.\n";
                pressEnterToContinue();
                clearline();
                clearline();
                clearline();
            }
        }
    } while (pilihan != 0);

    clearline();
    clearline();
    clearline();
    clearline();
    clearline();
    clearline();
}

void SistemSeminar::countdownSeminar(const Peserta &p)
{
    if (p.pilihan_seminar.empty())
    {
        cout << "\n(Tidak ada seminar yang terdaftar.)\n";
        pressEnterToContinue();
        return;
    }

    cout << "\n--- COUNTDOWN SEMINAR ANDA ---\n";

    for (const string &namaSem : p.pilihan_seminar)
    {
        InfoSeminar info;
        bool ada = cariInfoSeminar(namaSem, info);

        cout << "\n[ " << namaSem << " ]\n";

        if (ada)
        {
            cout << "  Tempat  : " << info.tempat << "\n";
            cout << "  Pengisi : " << info.pengisi << "\n";
            cout << "  Jadwal  : " << formatWaktu(info.waktu) << "\n";

            auto sekarang = chrono::system_clock::now();
            auto durasi = info.waktu - sekarang;

            if (durasi.count() <= 0)
            {
                cout << "  Status  : Seminar sudah berlangsung.\n";
            }
            else
            {
                long long total_detik = durasi.count() / 1000000000LL;
                long long hari = total_detik / 86400;
                long long jam = (total_detik % 86400) / 3600;
                long long menit = (total_detik % 3600) / 60;
                long long detik = total_detik % 60;

                cout << "  Countdown: " << hari << " hari, "
                     << jam << " jam, "
                     << menit << " menit, "
                     << detik << " detik\n";
            }
        }
        else
        {
            cout << "  [Info seminar tidak ditemukan/telah dihapus admin]\n";
        }
    }

    pressEnterToContinue();

    clearline();
    clearline();
    for (size_t i = 0; i < p.pilihan_seminar.size(); i++)
    {
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
    }
    clearline(); // "Press Enter..."
}

void SistemSeminar::menuAdmin()
{
    string inUser, inPass;
    cout << "\n--- LOGIN ADMIN ---\nUsername: ";
    cin >> inUser;
    cout << "Password: ";
    cin >> inPass;
    cin.ignore();

    if (inUser != "admin" || inPass != "admin123")
    {
        cout << "Login gagal!";
        pressEnterToContinue();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        return;
    }

    clearline();
    clearline();
    clearline();
    clearline();

    int pilihan;
    do
    {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Lihat Antrean\n";
        cout << "2. Verifikasi Peserta\n";
        cout << "3. Lihat Riwayat\n";
        cout << "4. Delete Peserta\n";
        cout << "5. Menambah Seminar\n";
        cout << "6. Menghapus Seminar\n";
        cout << "7. Lihat Daftar Seminar\n";
        cout << "0. Log Out\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();
        clearline();

        // Tampilkan antrean
        if (pilihan == 1)
        {
            antrean.tampilkan();
        }
        // Verifikasi (hapus dari antrean dan tumpuk pada riwayat)
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
            pressEnterToContinue();
            clearline();
            clearline();
            clearline();
        }
        // Tampilkan riwayat peserta
        else if (pilihan == 3)
        {
            riwayat.tampilkanSemua();
            pressEnterToContinue();
            clearline();
            clearline();
        }
        // Delete user by NIU
        else if (pilihan == 4)
        {
            string niu;
            cout << "Masukkan NIU peserta yang ingin dihapus: ";
            getline(cin, niu);

            bool ditemukan = false;
            if (antrean.hapusByNIU(niu))
            {
                cout << ">> Peserta dihapus dari antrean.\n";
                ditemukan = true;
            }
            if (riwayat.hapusByNIU(niu))
            {
                cout << ">> Peserta dihapus dari riwayat.\n";
                ditemukan = true;
            }
            if (!ditemukan)
                cout << ">> Peserta dengan NIU tersebut tidak ditemukan.\n";

            pressEnterToContinue();
            clearline();
            clearline();
            clearline();
            clearline();
            clearline();
        }
        // Tambah seminar
        else if (pilihan == 5)
        {
            cout << "\n--- TAMBAH SEMINAR BARU ---\n";

            string nama, tempat, pengisi, waktu_str;

            cout << "Nama Seminar    : ";
            getline(cin, nama);
            cout << "Tempat          : ";
            getline(cin, tempat);
            cout << "Pengisi Materi  : ";
            getline(cin, pengisi);
            cout << "Jadwal (format YYYY-MM-DD HH:MM): ";
            getline(cin, waktu_str);

            // Validasi format dasar
            if (waktu_str.size() < 16)
            {
                cout << "[!] Format waktu tidak valid. Seminar tidak ditambahkan.\n";
            }
            else
            {
                InfoSeminar baru(nama, tempat, pengisi, waktu_str);
                daftar_seminar.push_back(baru);
                cout << ">> Seminar \"" << nama << "\" berhasil ditambahkan!\n";
                cout << "   Jadwal : " << formatWaktu(baru.waktu) << "\n";
            }

            pressEnterToContinue();
            clearline();
            clearline();
            clearline();
            clearline();
            clearline();
            clearline();
            clearline();
            clearline();
        }
        // Hapus seminar
        else if (pilihan == 6)
        {
            if (daftar_seminar.empty())
            {
                cout << "Tidak ada seminar yang tersedia untuk dihapus.\n";
                pressEnterToContinue();
                clearline();
                clearline();
            }
            else
            {
                cout << "\n--- HAPUS SEMINAR ---\n";
                for (size_t i = 0; i < daftar_seminar.size(); i++)
                {
                    cout << i + 1 << ". " << daftar_seminar[i].nama
                         << " | " << formatWaktu(daftar_seminar[i].waktu) << "\n";
                }

                int hapusIndex;
                cout << "Masukkan nomor seminar yang ingin dihapus (0 untuk batal): ";
                cin >> hapusIndex;
                cin.ignore();

                if (hapusIndex > 0 && hapusIndex <= (int)daftar_seminar.size())
                {
                    cout << ">> Seminar \"" << daftar_seminar[hapusIndex - 1].nama << "\" berhasil dihapus!\n";
                    daftar_seminar.erase(daftar_seminar.begin() + (hapusIndex - 1));
                }
                else if (hapusIndex != 0)
                {
                    cout << "[!] Nomor tidak valid.\n";
                }

                pressEnterToContinue();
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
                for (size_t i = 0; i < daftar_seminar.size() + 1; i++)
                    clearline();
            }
        }
        // Lihat daftar seminar
        else if (pilihan == 7)
        {
            if (daftar_seminar.empty())
            {
                cout << "Tidak ada seminar yang terdaftar.\n";
            }
            else
            {
                cout << "\n=== DAFTAR SEMINAR ===\n";
                for (size_t i = 0; i < daftar_seminar.size(); i++)
                {
                    const InfoSeminar &s = daftar_seminar[i];
                    cout << i + 1 << ". " << s.nama << "\n";
                    cout << "   Tempat  : " << s.tempat << "\n";
                    cout << "   Pengisi : " << s.pengisi << "\n";
                    cout << "   Jadwal  : " << formatWaktu(s.waktu);
                    if (s.sudahLewat())
                        cout << "  [SUDAH LEWAT]";
                    cout << "\n\n";
                }
            }
            pressEnterToContinue();
            clearline();
            clearline();
            for (size_t i = 0; i < daftar_seminar.size(); i++)
            {
                clearline();
                clearline();
                clearline();
                clearline();
                clearline();
            }
        }

    } while (pilihan != 0);
}

//  Simpan data ke file
//  Format baris seminar: SEMINAR|nama|tempat|pengisi|waktu_str
//  Format antrean peserta: Q|nama|email|telp|NIU|prodi|sem1,sem2
//  Format riwayat peserta: S|nama|email|telp|NIU|prodi|sem1,sem2,,
void SistemSeminar::simpanData()
{
    ofstream file("database.txt");
    if (!file.is_open())
        return;

    // Simpan daftar seminar (termasuk yang ditambah admin)
    for (const auto &s : daftar_seminar)
    {
        file << "SEMINAR|" << s.nama << "|" << s.tempat << "|"
             << s.pengisi << "|" << s.waktu_str << "\n";
    }

    // Simpan antrean
    Node *tempQ = antrean.getFront();
    while (tempQ != nullptr)
    {
        file << "Q|" << tempQ->data.nama << "|" << tempQ->data.email << "|"
             << tempQ->data.telp << "|" << tempQ->data.NIU << "|"
             << tempQ->data.prodi << "|";
        for (const string &sem : tempQ->data.pilihan_seminar)
            file << sem << ",";
        file << "\n";
        tempQ = tempQ->next;
    }

    // Simpan riwayat
    Node *tempS = riwayat.getTop();
    while (tempS != nullptr)
    {
        file << "S|" << tempS->data.nama << "|" << tempS->data.email << "|"
             << tempS->data.telp << "|" << tempS->data.NIU << "|"
             << tempS->data.prodi << "|";
        for (const string &sem : tempS->data.pilihan_seminar)
            file << sem << ",";
        file << "\n";
        tempS = tempS->next;
    }
    file.close();
}

void SistemSeminar::muatData()
{
    ifstream file("database.txt");
    if (!file.is_open())
        return;

    // Kumpulkan nama seminar bawaan agar tidak duplikat
    auto namaAda = [&](const string &n) -> bool
    {
        for (const auto &s : daftar_seminar)
            if (s.nama == n)
                return true;
        return false;
    };

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string tipe;
        getline(ss, tipe, '|');

        if (tipe == "SEMINAR")
        {
            string nama, tempat, pengisi, waktu_str;
            getline(ss, nama, '|');
            getline(ss, tempat, '|');
            getline(ss, pengisi, '|');
            getline(ss, waktu_str, '|');

            if (!namaAda(nama))
                daftar_seminar.push_back(InfoSeminar(nama, tempat, pengisi, waktu_str));
            else
            {
                // Update data seminar bawaan dengan data dari file
                for (auto &s : daftar_seminar)
                {
                    if (s.nama == nama)
                    {
                        s = InfoSeminar(nama, tempat, pengisi, waktu_str);
                        break;
                    }
                }
            }
        }
        else if (tipe == "Q" || tipe == "S")
        {
            string nama, email, telp, NIU, prodi, seminarList;
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
            else
                riwayat.push(p);
        }
    }
    file.close();
}

void clearline()
{
    std::cout << "\033[A\033[2K";
    std::flush(std::cout);
}

void pressEnterToContinue()
{
    cout << "\nPress Enter to continue...";
    cin.get();
    clearline();
}