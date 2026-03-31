#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

struct Data
{
    string nama;
    string email;
    int NIU;
    string prodi;
    int pilihan;
};

struct Node
{
    Data info;
    Node *next;
};

extern Node *head;

// Fungsi
void insert(Data d);
void display();
void searchData(string nama);
void deleteData(string nama);

#endif