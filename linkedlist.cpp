#include "linkedlist.h"

Node *head = NULL;

void insert(Data d)
{
    Node *newNode = new Node;
    newNode->info = d;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void display()
{
    if (head == NULL)
    {
        cout << "Data kosong.\n";
        return;
    }
}