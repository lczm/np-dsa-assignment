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
    size++;
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
    size++;
}

template <typename T>
void DoublyLinkedList<T>::addAt(T& newNode, int index)
{
     ListNode<T>* beforeIndexNode;

     ListNode<T> * newListNode = new ListNode<T>();
     newListNode->node = newNode;

     if (index >= 0 and index <= size)
      { 
        if (index == 0)
        {
            newListNode->next = front;
            front->prev = newListNode;
            front = newListNode;
        }    
        else
        {
            ListNode<T>* traverseNode = front;
            for (int i = 0; i < index-1; i++)
            {
              traverseNode = traverseNode->next;
            }

            beforeIndexNode = traverseNode;
            newListNode->prev = beforeIndexNode;
            newListNode->next = beforeIndexNode->next;

            if (beforeIndexNode->next != nullptr)
            {
                beforeIndexNode->next->prev = newListNode;
            }

            beforeIndexNode->next = newListNode;
        }

        size++;
     }
}

template <typename T>
void DoublyLinkedList<T>::removeByListNodePtr(ListNode<T>* listNodeptr)
{
    if (size > 0)
    {

        if (listNodeptr->prev == nullptr)
        {   
            front = listNodeptr->next;
            if (front != nullptr)
            {
                front->prev = nullptr;
            }
            listNodeptr->next = nullptr;
        }
        else if (listNodeptr->next == nullptr)
        {
            end = listNodeptr->prev;
            if (end != nullptr)
            {
                end->next = nullptr;
            }
            listNodeptr->prev = nullptr;
        }
        else
        {
            listNodeptr->prev->next = listNodeptr->next;
            listNodeptr->next->prev = listNodeptr->prev;
        }

        delete listNodeptr;
        size--;
    }
}

template <typename T>
void DoublyLinkedList<T>::remove(T& nodeToRemove)
{
    if (size > 0)
    {
        ListNode<T>* traverseNode = front;
        while (traverseNode != nullptr)
        {
            if (traverseNode->node == nodeToRemove)
            {
                removeByListNodePtr(traverseNode);
                break;
            }
            traverseNode = traverseNode->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::removeAt(int index)
{
    if (size > 0)
    {
        if (index >= 0 and index < size)
        {
            ListNode<T>* traverseNode = front;
            for (int i = 0; i < index; i++)
            {
                traverseNode = traverseNode->next;
            }

            removeByListNodePtr(traverseNode);
        }
    }
}

template <typename T>
T DoublyLinkedList<T>::getAt(int index)
{
    if (size > 0 and index < size)
    {   
        if (index >=0 and index < size)
        {
            ListNode<T>* traverseNode = front;
            for (int i = 0; i < index; i++)
            {
                traverseNode = traverseNode->next;
            }

            return traverseNode->node;
        }
    }

}

template <typename T>
int DoublyLinkedList<T>::getSize()
{
    return size;
}

#endif