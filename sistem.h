#ifndef SISTEMSEMINAR_H
#define SISTEMSEMINAR_H

#include "datastruktur.h"
#include <vector>
#include <string>

class SistemSeminar
{
private:
    AntreanRegistrasi antrean;
    RiwayatVerifikasi riwayat;
    vector<string> daftar_seminar;

    void menuUser();
    void menuAdmin();

    void simpanData();
    void muatData();

public:
    SistemSeminar();
    ~SistemSeminar(); // Destructor untuk menyimpan data saat program keluar
    void jalankan();
};

#endif