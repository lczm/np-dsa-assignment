#ifndef _DOUBLYLINKEDLIST_
#define _DOUBLYLINKEDLIST_


#include "DoublyLinkedList.h"


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{

    front = nullptr;
    end = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::addFront(T& newNode)
{
    ListNode<T> * newListNode = new ListNode<T>();
    newListNode->node = newNode;
    newListNode->next = front;
    newListNode->prev = nullptr;

    if (front == nullptr)
    {
        end = newListNode;
    }
    else
    {
        front->prev = newListNode;
    }

    front = newListNode;
}

template <typename T>
void DoublyLinkedList<T>::addBack(T& newNode)
{
    ListNode<T>* newListNode = new ListNode<T>();
    newListNode->node = newNode;
    newListNode->next = nullptr;
    newListNode->prev = end;

    if (end == nullptr)
    {
        front = newListNode;
    }
    else
    {
        end->next = newListNode;
    }

    end = newListNode;
}

#endif