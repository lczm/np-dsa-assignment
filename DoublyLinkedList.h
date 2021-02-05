#pragma once
#include <iostream>
using namespace std;
// Name: Abicharan Bhaskaran
// ID: S10177176J
// Group: 02
// Class: P07
template <typename T>
struct ListNode
{   
    T node;
    ListNode<T>* prev;
    ListNode<T>* next;
};

template <typename T>
class DoublyLinkedList
{   
    private:
        ListNode<T>* front; //Points to the front of the doubly-linked list
        ListNode<T>* end;   //Points to the end of the doubly-linked list
        int size = 0;

    public:
     DoublyLinkedList();
     ListNode<T>* getFrontPtr()
     {
         return front;
     }

     // Adds to the front of the DLL (Doubly-linked-list)
     void addFront(T& newNode);

     
     // Adds to the back of the DLL (Doubly-linked-list)
     void addBack(T& newNode);

     
     // Adds to the index of the DLL (Doubly-linked-list)
     void addAt(T& newNode, int index);

     // Removes the item based on the ListNode pointer provided
     void removeByListNodePtr(ListNode<T>* listNodeptr);

     void remove(T& nodeToRemove);

     //Removes the data at the specified index
     void removeAt(int index);

     //Gets the data at the specified index
     T getAt(int index);

     //Gets the size of the Doubly-linked list
     int getSize();
};

#include "DoublyLinkedList.cpp"