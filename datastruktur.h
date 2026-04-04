#ifndef DATASTRUKTUR_H
#define DATASTRUKTUR_H

#include "peserta.h"
#include <iostream>

using namespace std;

class Node
{
public:
    Peserta data;
    Node *next;
    Node(Peserta p) : data(p), next(nullptr) {}
};

// --- STACK (Untuk yang sudah diverifikasi) ---
class RiwayatVerifikasi
{
private:
    Node *top;

public:
    RiwayatVerifikasi() : top(nullptr) {}

    void push(Peserta p)
    {
        Node *newNode = new Node(p);
        newNode->next = top;
        top = newNode;
    }

    // Fungsi untuk cek status di Dashboard User (Sudah Verifikasi)
    bool cariPeserta(string nama, string niu, Peserta &p)
    {
        Node *temp = top;
        while (temp != nullptr)
        {
            if (temp->data.nama == nama && temp->data.NIU == niu)
            {
                p = temp->data;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void tampilkanSemua()
    {
        if (top == nullptr)
        {
            cout << "Riwayat pendaftaran masih kosong.\n";
            return;
        }
        Node *temp = top;
        cout << "\n=== RIWAYAT PESERTA DIVERIFIKASI ===\n";
        while (temp != nullptr)
        {
            cout << "Nama   : " << temp->data.nama << " (" << temp->data.NIU << ")\n";
            cout << "Seminar: ";
            for (const string &sem : temp->data.pilihan_seminar)
                cout << "- " << sem << " ";
            cout << "\n--------------------------------------------\n";
            temp = temp->next;
        }
    }

    void tampilkanTerakhir()
    {
        if (top == nullptr)
        {
            cout << "Belum ada peserta yang diverifikasi.\n";
        }
        else
        {
            cout << "\nPeserta Terakhir Diverifikasi:\n";
            cout << "Nama   : " << top->data.nama << "\n";
            cout << "NIU    : " << top->data.NIU << "\n";
        }
    }
    // Delete Peserta
    bool hapusByNIU(string niu)
    {
        Node *curr = top;
        Node *prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->data.NIU == niu)
            {
                if (prev == nullptr)
                    top = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    Node *getTop() { return top; }
};

// --- QUEUE (Untuk yang masih antre) ---
class AntreanRegistrasi
{
private:
    Node *front;
    Node *rear;

public:
    AntreanRegistrasi() : front(nullptr), rear(nullptr) {}

    void enqueue(Peserta p)
    {
        Node *newNode = new Node(p);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool dequeue(Peserta &p)
    {
        if (front == nullptr)
            return false;
        Node *temp = front;
        p = temp->data;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete temp;
        return true;
    }

    // Fungsi untuk cek status di Dashboard User (Masih Antre)
    bool cariPeserta(string nama, string niu, Peserta &p)
    {
        Node *temp = front;
        while (temp != nullptr)
        {
            if (temp->data.nama == nama && temp->data.NIU == niu)
            {
                p = temp->data;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void tampilkan()
    {
        if (front == nullptr)
        {
            cout << "Antrean registrasi kosong.\n";
            return;
        }
        Node *temp = front;
        int urutan = 1;
        cout << "\n=== ANTREAN REGISTRASI ===\n";
        while (temp != nullptr)
        {
            cout << urutan++ << ". " << temp->data.nama << " (" << temp->data.NIU << ")\n   Seminar: ";
            for (const string &sem : temp->data.pilihan_seminar)
                cout << "[" << sem << "] ";
            cout << "\n";
            temp = temp->next;
        }
    }
    // Delete Peserta   
    bool hapusByNIU(string niu)
    {
        Node *curr = front;
        Node *prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->data.NIU == niu)
            {
                if (prev == nullptr) // hapus di depan
                    front = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    Node *getFront() { return front; }
};

#endif