#ifndef PESERTA_H
#define PESERTA_H

#include <string>
#include <vector>
using namespace std;

class Peserta {
public:
    string nama;
    string email;
    string NIM;
    string prodi;
    string telp;
    vector<string> pilihan_seminar; 

    Peserta(string n = "", string e = "", string nim = "", string p = "", string t = "")
        : nama(n), email(e), NIM(nim), prodi(p), telp(t) {}
};

#endif