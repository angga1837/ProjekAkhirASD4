#ifndef SISTEMSEMINAR_H
#define SISTEMSEMINAR_H

#include "datastruktur.h"
#include <vector>
#include <string>
#include <chrono>

class SistemSeminar
{
private:
    AntreanRegistrasi antrean;
    RiwayatVerifikasi riwayat;
    vector<string> daftar_seminar;
    std::chrono::system_clock::time_point waktu_workshop;

    void menuUser();
    void menuAdmin();

    void simpanData();
    void muatData();

    void countdown();

public:
    SistemSeminar();
    ~SistemSeminar(); // Destructor untuk menyimpan data saat program keluar
    void jalankan();
};

#endif