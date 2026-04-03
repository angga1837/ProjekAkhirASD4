#ifndef PESERTA_H
#define PESERTA_H

#include <string>
#include <vector>
using namespace std;

class Peserta
{
public:
    string nama;
    string email;
    string NIU;
    string prodi;
    string telp;
    vector<string> pilihan_seminar;

    Peserta(string n = "", string e = "", string niu = "", string p = "", string t = "")
        : nama(n), email(e), NIU(niu), prodi(p), telp(t) {}
};

#endif