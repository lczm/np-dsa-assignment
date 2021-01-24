#pragma once
// Dictionary.h - - Specification of Dictionary ADT
#include<string>
#include<iostream>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
struct DictionaryNode
{
	string  key;   // search key
	T item;	// data item
    DictionaryNode<T>* next;  // pointer pointing to next item
};

template <typename T>
class Dictionary
{
private:
    DictionaryNode<T>* items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:
	// constructor
	Dictionary();

	// destructor
	~Dictionary();

	int hash(string key);

	// add a new item with the specified key to the Dictionary
    bool add(string newKey, T newItem);

	// remove an item with the specified key in the Dictionary
    void remove(string key);

	// get an item with the specified key in the Dictionary (retrieve)
    T get(string key);

	// check if the Dictionary is empty
	bool isEmpty();

	// check the size of the Dictionary
	int getLength();
    int charvalue(char c)
    {
        if (isalpha(c))
        {
           if (isupper(c))
               return (int)c - (int)'A';
           else
              return (int)c - (int)'a' + 26;
        }
        else
            return -1;
    }
    int code(char c)
    {
       return (int)c;
    }
};



#include "Dictionary.cpp"