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
    vector<InfoSeminar> daftar_seminar; 
 
    void menuUser();
    void menuAdmin();
 
    void simpanData();
    void muatData();
 
    void countdownSeminar(const Peserta &p);
 
    bool cariInfoSeminar(const string &nama, InfoSeminar &out) const;
 
public:
    SistemSeminar();
    ~SistemSeminar();
    void jalankan();
};
 
#endif