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
    if (key == 32)
    {
        return 0;
    }
    else if (key >= 48 && key <= 57)  // 0-9
    {
        return key - 48 + 1;
    }
    else if (key >= 65 && key <= 90)  // A-Z
    {
        return key - 65 + 10 + 1;
    }
    else if (key >= 97 && key <= 122)  // a-z
    {
        // Shift it down to the A-Z character set
        // then calculate index, minus 65, add the
        // offset of 10 (numbers)
        return key - (97 - 65) - 65 + 10 + 1;
    }
    else
    {
        cout << "Key not supported. Only 0-9 and A-z" << endl;
    }
}

// This assumes all upper case.
char Trie::getChar(uint32_t index)
{
    if (index == 0)
    {
        return 32;
    }
    else if (index >= 1 && index <= 10)
    {
        // return index - 1;
        return index + 48 - 1;
    }
    else if (index >= 11 && index <= 37)
    {
        return index + 65 - 10 - 1;
    }
}

bool Trie::isLastNode(TrieNode* node)
{
    for (uint32_t i = 0; i < TRIE_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}

void Trie::suggestions(TrieNode* node, string prefix, Vector<string>& completions)
{
    if (node->end)
    {
        // completions.push_back(prefix);
        completions.pushBack(prefix);
    }

    // If it is the last node, return as you cannot further recurse
    if (isLastNode(node))
    {
        return;
    }

    // Go over every possible index
    for (uint32_t i = 0; i < TRIE_SIZE; i++)
    {
        // If the children exists, then get it.
        if (node->children[i] != nullptr)
        {
            // Add the child character to the prefix.
            prefix += getChar(i);

            // Recurse down, if the recurse-d children does not
            // have anything, this will return with nothing.
            suggestions(node->children[i], prefix, completions);

            // Remove it afterwards, as the other words
            // do not require this.
            prefix.pop_back();
        }
    }
}

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

// TODO : Search word vs search exist
bool Trie::search(string key)
{
    TrieNode* traversal = root;

    for (uint32_t i = 0; i < key.size(); i++)
    {
        uint32_t index = getIndex(key[i]);
        if (traversal->children[index] == nullptr)
        {
            return false;
        }
        traversal = traversal->children[index];
    }

    if (traversal->end)
        return true;
    else
        return false;
}

Vector<string> Trie::complete(string key)
{
    // TODO : Check that the key exists within the trie
    // before trying to complete.

    // Key exists. Store the rest of the completions in a Vector
    TrieNode* traversal = root;
    for (uint32_t i = 0; i < key.size(); i++)
    {
        uint32_t index = getIndex(key[i]);
        traversal = traversal->children[index];
    }

    Vector<string> completions;

    // No further keys to look for, return empty vector
    if (isLastNode(traversal)) return completions;

    // Populate completions with values
    suggestions(traversal, key, completions);

    return completions;
}