#ifndef _DICTIONARY_
#define _DICTIONARY_

#include "Dictionary.h"



template <typename T>
Dictionary<T>::Dictionary()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        items[i] = NULL;
    }

    size = 0;
}

template <typename T>
Dictionary<T>::~Dictionary()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (items[i] != NULL)
        {
            DictionaryNode<T>* traverseNode = items[i];
            DictionaryNode<T>* prevNode = NULL;
            while (traverseNode != NULL)
            {
                prevNode = traverseNode;
                traverseNode = traverseNode->next;
                delete prevNode;
                prevNode = NULL;
            }
        }

    }

}




template <typename T>
int Dictionary<T>::hash(string key)
{   
    int convertedHash = 0;

    for (int i = 0; i < key.length(); i++)
    {   

        convertedHash = (convertedHash + i * code(key[i])) % MAX_SIZE;

        //convertedHash = (int)(charvalue(key[i]) * pow(52, key.length() - (i + 1))) % MAX_SIZE;

    }

    return convertedHash;
}


template <typename T>
bool Dictionary<T>::add(string newKey, T newItem)
{
    int hashedValue = hash(newKey);

    DictionaryNode<T>* newNode = new DictionaryNode<T>();
    newNode->item = newItem;
    newNode->key = newKey;

    if (items[hashedValue] == NULL)
    {
        items[hashedValue] = newNode;
    }
    else {
        DictionaryNode<T>* traverseNode = items[hashedValue];
        DictionaryNode<T>* prevNode = nullptr;
        while (traverseNode != NULL)
        {
            if (traverseNode->key == newNode->key) {
                return false;
            }
            prevNode = traverseNode;
            traverseNode = traverseNode->next;
        }
        prevNode->next = newNode;
    }

    size += 1;
    return true;
}
template <typename T>
void Dictionary<T>::remove(string key)
{
    if (!isEmpty())
    {
        int hashedValue = hash(key);
        if (items[hashedValue] == NULL)
        {
            return;
        }
        else if (items[hashedValue]->key == key) {

            DictionaryNode<T>* nextNode = items[hashedValue]->next;
            delete items[hashedValue];
            items[hashedValue] = nextNode;
            size -= 1;
            return;
        }
        else {
            DictionaryNode<T>* traverseNode = items[hashedValue];
            
            while (traverseNode->next != NULL && traverseNode->next->key != key)
            {   
                traverseNode = traverseNode->next;
            }

            //Special case if the key thats wanted to be removed is not there in the linked list
            //will return an exception otherwise
            if (traverseNode->next != NULL)
            {
                DictionaryNode<T>* deletedNode = traverseNode->next;
                traverseNode->next = deletedNode->next;
                deletedNode->next = NULL;
                delete deletedNode;
                size -= 1;
            }
            
        }

    }
}

template <typename T>
T Dictionary<T>::get(string key)
{   
    if (!isEmpty())
    {
        int hashedValue = hash(key);
        if (items[hashedValue] != NULL)
        {
            if (items[hashedValue]->next == NULL) {

                //in the case that there is only 1 value and it does not
                //correspond to the key being deleted
                if (items[hashedValue]->key == key)
                {
                    return items[hashedValue]->item;
                }
            }
            else {
                DictionaryNode<T>* traverseNode = items[hashedValue];
                while (traverseNode->key != key)
                {
                    traverseNode = traverseNode->next;
                }

                return traverseNode->item;
            }
        }
    }

}

template <typename T>
bool Dictionary<T>::isEmpty()
{
    return size <= 0;
}

template <typename T>
int Dictionary<T>::getLength()
{
    return size;
}


#endif