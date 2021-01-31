#include "trie.h"

Trie::Trie()
{
    root = new TrieNode();
}

Trie::~Trie()
{
    delete root;
}

uint32_t Trie::getIndex(char key)
{
    if (key >= 48 && key <= 57)  // 0-9
    {
        return key - 48;
    }
    else if (key >= 65 && key <= 90)  // A-Z
    {
        return key - 65 + 10;
    }
    else if (key >= 97 && key <= 122)  // a-z
    {
        // Shift it down to the A-Z character set
        // then calculate index, minus 65, add the
        // offset of 10 (numbers)
        return key - (97 - 65) - 65 + 10;
    }
    else
    {
        cout << "Key not supported. Only 0-9 and A-z" << endl;
    }
}

// char Trie::getChar(uint32_t index)
// {
// }

void Trie::insert(string key)
{
    TrieNode* traversal = root;

    for (uint32_t i = 0; i < key.size(); i++)
    {
        uint32_t index = getIndex(key[i]);
        if (traversal->children[index] == nullptr)
        {
            traversal->children[index] = new TrieNode();
        }
        traversal = traversal->children[index];
    }

    // After iterating over the key, it is the 'end' of the node.
    traversal->end = true;
}

bool Trie::search(string key)
{
    TrieNode* traversal = root;

    for (uint32_t i = 0; i < key.size(); i++)
    {
        uint32_t index = getIndex(key[i]);
        if (traversal->children[index] == nullptr)
        {
            cout << "returning false : " << key[i] << endl;
            return false;
        }
        traversal = traversal->children[index];
    }

    if (traversal->end)
        return true;
    else
        return false;
}

// TODO : Check that this can be done in one pass?
// searching is one pass, and completing is one pass.
// possibly inefficient if the trie is really large.
void Trie::complete(string key)
{
    // Check that the key exists within the trie
    // before trying to complete.
    if (!search(key))
    {
        // Key does not exist, return empty vector
        cout << "Key does not exist" << endl;
        return;
    }

    // Key exists. Store the rest of the completions in a Vector
    TrieNode* traversal = root;
    for (uint32_t i = 0; i < key.size(); i++)
    {
        uint32_t index = getIndex(key[i]);
        traversal = traversal->children[index];
    }

    if (!traversal->end)
    {
    }
}