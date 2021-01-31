#pragma once

#include <string>
#include <iostream>

using namespace std;

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

    Therefore, the trie node children will need to have a size of
    26 + 10 = 36.

  The trie children layout will also need to be determined.
    For the 36 characters, how will each of them be laid out.

    It will be laid out as such
    < ----------------------------------------------------- > Len : 36
    < ----------- > (10) < -------------------------------- > (26)
    < ----0-9---- > (10) < ---------------A-Z-------------- > (26)

    It is important that the layout stays the same and consistent.
    So that the TrieNode is able to access it's children by
    O(1) time complexity.

  Edge cases:
    There are some situations in which, the trie may not be able to deal
    with effectively. One situation that comes to mind is dealing with
    capital cases.

    'a' and 'A' are two different characters effectively.

    The dataset stores 'ALJUNIED', which are all caps-ed.
    However, the user might type 'aljunied'. It is expected that
    'ALJUNIED' will still be found even though the search key is
    'aljunied'.

    How this can be dealt with can be through preprocessing all
    key units to be the case that is held in the tree. Storing the
    indies, such that when returning the result back to the user,
    it will be in the cases that the user typed in. This will be
    more user friendly and intuitive.
 */

const int TRIE_SIZE = 36;

struct TrieNode
{
    struct TrieNode* children[TRIE_SIZE];
    bool end = false;
};

class Trie
{
    // Private Attributes
   private:
    TrieNode* root = nullptr;

    // Private methods
   private:
    uint32_t getIndex(char key);

    // Public methods
   public:
    Trie();
    ~Trie();

    void insert(string key);
    void search(string key);
};