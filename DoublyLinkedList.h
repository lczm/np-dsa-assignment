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

    public:
     DoublyLinkedList();
     void addFront(T& newNode);
     void addBack(T& newNode);
    
       
    
};

#include "DoublyLinkedList.cpp"