#pragma once

#include <string>
#include <iostream>
#include "vector.h"

using namespace std;

// Name: Chua Ze Ming
// ID: S10177361C
// Group: 02
// Class: P07

/*
 Determining how big a node should hold:
    This is done by determining the range of values that
    the trie structure is going to deal with.

    In that context, this can also be done by looking at
    the data that will be passed in.

    The trie structure will be used for all the use cases
    that require 'searches.'

    By looking at the dataset, there are two main cases:
      1. EW10
      2. ALJUNIED MRT STATION

    Hence, it will need to deal with the basic alphabets (A-Z).
    There are 26 of those. And 0-9. There are 10 of these.

    The trie will also need to deal with spaces, as the user may type
    spaces. That will take up another space / commas / dashes

    Therefore, the trie node children will need to have a size of
    26 + 26 + 10 + 3 = 65.

  The trie children layout will also need to be determined.
    For the 36 characters, how will each of them be laid out.

    It will be laid out as such
    < --------------------------------------------------------------- > Len : 65
    < -- > (3) < ----------- > (10) < -------------------------------> (26 * 2)
    < () > (3) < ----0-9---- > (10) < ---------------A-z------------ > (26 * 2)

    It is important that the layout stays the same and consistent.
    So that the TrieNode is able to access it's children by
    O(1) time complexity.
 */

const int TRIE_SIZE = 65;

struct TrieNode
{
    TrieNode* children[TRIE_SIZE];
    bool end = false;

    // Initialize all children to nullptr
    TrieNode()
    {
        for (uint32_t i = 0; i < TRIE_SIZE; i++)
        {
            children[i] = nullptr;
        }
    }
};

class Trie
{
    // Private Attributes
   private:
    TrieNode* root = nullptr;

    // Private methods
   private:
    uint32_t getIndex(char key);
    char getChar(uint32_t index);
    bool isLastNode(TrieNode* node);
    void suggestions(TrieNode* node, string prefix, Vector<string>& completions);
    uint32_t numberOfChildren(TrieNode* node);

    // Public methods
   public:
    Trie();
    Trie(Vector<string> in);
    ~Trie();

    // insert a key
    void insert(string key);

    // insert a collection of keys
    void insert(Vector<string> keys);

    // returns true if the key is contained in the trie
    bool contains(string key);

    // returns true if the key is a word
    bool search(string key);

    // removes the key from the trie
    void remove(string key);

    // returns a list of completions that can be completed from the key
    Vector<string> complete(string key);
};