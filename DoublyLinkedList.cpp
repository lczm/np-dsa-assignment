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

    //if the front is empty this means
    //that both front and end must point to the new node
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

    //If the endNode if empty this means
    //that the front and end must point to the new node
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
            //traverse to the node before
            ListNode<T>* traverseNode = front;
            for (int i = 0; i < index-1; i++)
            {
              traverseNode = traverseNode->next;
            }

            //Update info for the new node
            beforeIndexNode = traverseNode;
            newListNode->prev = beforeIndexNode;
            newListNode->next = beforeIndexNode->next;

            //check if the next node is not null
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
        // This means the listNode is the front ptr
        if (listNodeptr->prev == nullptr)
        {   
            front = listNodeptr->next;

            //if front is not null
            if (front != nullptr)
            {
                front->prev = nullptr;
            }

            //make the listNode to be deleted point to nothing
            listNodeptr->next = nullptr;
        }

        //This means the listnode to be deleted is the end ptr
        else if (listNodeptr->next == nullptr)
        {
            //Set end to the previous listNode ptr
            end = listNodeptr->prev;
            if (end != nullptr)
            {
                end->next = nullptr;
            }

            //Make the listNode to be deleted point to nothing
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

            //Traverse and get the listNodeptr
            ListNode<T>* traverseNode = front;
            for (int i = 0; i < index; i++)
            {
                traverseNode = traverseNode->next;
            }

            //Pass it onto the function 
            //which removes by the pointer
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