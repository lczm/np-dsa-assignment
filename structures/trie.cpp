#include "trie.h"

Trie::Trie()
{
    root = new TrieNode();
}

Trie::Trie(Vector<string> in)
{
    root = new TrieNode();

    // If passed in a vector as the constructor, insert all of the values
    // into the trie.
    for (uint32_t i = 0; i < in.size(); i++)
    {
        insert(in[i]);
    }
}

Trie::~Trie()
{
    delete root;
}

uint32_t Trie::getIndex(char key)
{
    // Spaces, Commas, Dashes, Colons, Semi-Colons
    if (key == 32 || key == 44)
    {
        return 0;
    }
    else if (key == 45)  // Dashes
    {
        return 1;
    }
    else if (key == 58)  // Colons
    {
        return 2;
    }
    else if (key >= 48 && key <= 57)  // 0-9
    {
        return key - 48 + 3;
    }
    else if (key >= 65 && key <= 90)  // A-Z
    {
        return key - 65 + 10 + 3;
    }
    else if (key >= 97 && key <= 122)  // a-z
    {
        // Offset the 26 the is caused by A-Z
        // Offset the 10 numbers
        // Offset the 3 special digits
        return key - 97 + 26 + 10 + 3;
    }
    else
    {
        cout << "Key not supported. Only 0-9 and A-z" << endl;
    }
}

// This assumes all upper case.
char Trie::getChar(uint32_t index)
{
    if (index == 0)  // Spaces
    {
        return 32;
    }
    else if (index == 1)  // Dashes
    {
        return 45;
    }
    else if (index == 2)  // Colons
    {
        return 58;
    }
    else if (index >= 3 && index <= 12)  // Numbers
    {
        // return index - 1;
        return index + 48 - 3;
    }
    else if (index >= 13 && index <= 38)  // A-Z
    {
        return index + 65 - 10 - 3;
    }
    else if (index >= 39 && index <= 65)  // a-z
    {
        return index + 97 - 26 - 10 - 3;
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

uint32_t Trie::numberOfChildren(TrieNode* node)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < TRIE_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            count++;
        }
    }

    return count;
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

void Trie::insert(Vector<string> keys)
{
    for (uint32_t i = 0; i < keys.size(); i++)
    {
        insert(keys[i]);
    }
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

void Trie::remove(string key)
{
    // TODO : Check that key exists within the trie
    // before trying to remove

    // Trie is not initialized
    if (root == nullptr)
    {
        return;
    }

    TrieNode* traversal = root;
    Vector<TrieNode*> nodeStack;

    // For each character in the input to remove
    // Build up the nodeStack
    for (char c : key)
    {
        traversal = traversal->children[getIndex(c)];
        nodeStack.pushBack(traversal);
    }

    // If at the end, and if it is the end, set it to not be the last
    if (traversal->end) traversal->end = false;

    while (!nodeStack.isEmpty())
    {
        TrieNode* node = nodeStack.back();
        nodeStack.pop();

        // Get which character it is
        uint32_t index = nodeStack.size();

        // If it is not the last node
        if (numberOfChildren(node) > 1 || nodeStack.isEmpty())
        {
            node->children[key[index]] = nullptr;
        }
    }
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