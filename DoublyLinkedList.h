#pragma once
#include <iostream>
using namespace std;

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
        ListNode<T>* front;
        ListNode<T>* end;
        int size = 0;

    public:
     DoublyLinkedList();
     ListNode<T>* getFrontPtr()
     {
         return front;
     }
     void addFront(T& newNode);
     void addBack(T& newNode);
     void remove(ListNode<T>* listNodeptr);
     int getSize();
       
    
};

#include "DoublyLinkedList.cpp"