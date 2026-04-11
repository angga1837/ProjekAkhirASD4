#ifndef PESERTA_H
#define PESERTA_H
 
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;
 
// Struct menyimpan info tiap seminar
struct InfoSeminar
{
    string nama;
    string tempat;
    string pengisi;
    string waktu_str;
    chrono::system_clock::time_point waktu;
 
    InfoSeminar() {}
 
    InfoSeminar(string n, string t, string p, string w_str)
        : nama(n), tempat(t), pengisi(p), waktu_str(w_str)
    {
        waktu = parseWaktu(w_str);
    }
 
    // Parse string "YYYY-MM-DD HH:MM" ke time_point
    static chrono::system_clock::time_point parseWaktu(const string &w)
    {
        tm tm = {};
        // format: YYYY-MM-DD HH:MM, untuk satuan ditulis dengan awalan 0, misal jam 7 atau tanggal 7 ditulis 07
        if (w.size() >= 16)
        {
            tm.tm_year = stoi(w.substr(0, 4)) - 1900;
            tm.tm_mon  = stoi(w.substr(5, 2)) - 1;
            tm.tm_mday = stoi(w.substr(8, 2));
            tm.tm_hour = stoi(w.substr(11, 2));
            tm.tm_min  = stoi(w.substr(14, 2));
            tm.tm_sec  = 0;
            tm.tm_isdst = -1;
        }
        return chrono::system_clock::from_time_t(mktime(&tm));
    }
 
    bool sudahLewat() const
    {
        return chrono::system_clock::now() >= waktu;
    }
};
 
class Peserta
{
public:
    string nama;
    string email;
    string NIU;
    string prodi;
    string telp;
    // Hanya menyimpan nama seminar yang dipilih (detail dicari dari daftar_seminar)
    vector<string> pilihan_seminar;
 
    Peserta(string n = "", string e = "", string niu = "", string p = "", string t = "")
        : nama(n), email(e), NIU(niu), prodi(p), telp(t) {}
};
 
void clearline();
void pressEnterToContinue();
 
#endif