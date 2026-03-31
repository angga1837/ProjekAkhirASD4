#ifndef DATASTRUKTUR_H
#define DATASTRUKTUR_H

#include "peserta.h"
#include <iostream>

class Node {
public:
    Peserta data;
    Node* next;
    Node(Peserta p) : data(p), next(nullptr) {}
};

//stack
class RiwayatVerifikasi {
private:
    Node* top;

public:
    RiwayatVerifikasi() : top(nullptr) {}

    void push(Peserta p) {
        Node* newNode = new Node(p);
        newNode->next = top;
        top = newNode;
    }

    void tampilkanSemua() {
        if (top == nullptr) {
            cout << "Riwayat registrasi masih kosong.\n";
            return;
        }
        Node* temp = top;
        cout << "\n=== RIWAYAT PESERTA DIVERIFIKASIO===\n";
        while (temp != nullptr) {
            cout << "Nama   : " << temp->data.nama << " (" << temp->data.NIM << ")\n";
            cout << "Seminar: ";
            for (const string& sem : temp->data.pilihan_seminar) cout << "- " << sem << " ";
            cout << "\n--------------------------------------------\n";
            temp = temp->next;
        }
    }

    void tampilkanTerakhir() {
        if (top == nullptr) {
            cout << "Belum ada peserta yang diproses.\n";
        } else {
            cout << "\nPeserta Terakhir Diproses:\n";
            cout << "Nama   : " << top->data.nama << "\n";
            cout << "NIM    : " << top->data.NIM << "\n";
        }
    }

    Node* getTop() { return top; }
};

//queue
class AntreanRegistrasi {
private:
    Node* front;
    Node* rear;

public:
    AntreanRegistrasi() : front(nullptr), rear(nullptr) {}

    void enqueue(Peserta p) {
        Node* newNode = new Node(p);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool dequeue(Peserta& p) {
        if (front == nullptr) return false;
        Node* temp = front;
        p = temp->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return true;
    }

    void tampilkan() {
        if (front == nullptr) {
            cout << "Antrean registrasi kosong.\n";
            return;
        }
        Node* temp = front;
        int urutan = 1;
        cout << "\n=== ANTREAN REGISTRASI (QUEUE) ===\n";
        while (temp != nullptr) {
            cout << urutan++ << ". " << temp->data.nama << " (" << temp->data.NIM << ")" << " - " << temp->data.telp << "\nSeminar: ";
            for (const string& sem : temp->data.pilihan_seminar) cout << "[" << sem << "] ";
            cout << "\n";
            temp = temp->next;
        }
    }

    bool cariPeserta(string nama, string nim, Peserta& p) {
        Node* temp = front;
        while (temp != nullptr) {
            if (temp->data.nama == nama && temp->data.NIM == nim) {
                p = temp->data;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    Node* getFront() { return front; }
};

#endif