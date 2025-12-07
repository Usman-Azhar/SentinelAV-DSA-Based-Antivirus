#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "signature.h"

using namespace std;

// TrieNode: Single node in the prefix tree
// Each node represents one character in the pattern
struct TrieNode
{
    unordered_map<char, TrieNode *> children; // Map: 'a' → child node for 'a'
    bool isEndOfWord;                         // True = complete signature ends here
    Signature *sigData;                       // Store full details at word endings

    TrieNode() : isEndOfWord(false), sigData(nullptr) {}

    // Cleanup: Delete all child nodes recursively
    ~TrieNode()
    {
        if (sigData)
            delete sigData;
        for (auto &pair : children)
        {
            delete pair.second; // Recursively deletes entire subtree
        }
    }
};

// Trie (Prefix Tree): Efficient pattern matching structure
// Example: Storing "malware" and "malfunction"
//          root → m → a → l → w → a → r → e [END]
//                          ↓
//                          f → u → n → c... [END]
// Advantage: Shared prefixes save space, fast search O(m) where m = pattern length
class Trie
{
private:
    TrieNode *root;
    int signatureCount;

public:
    Trie() : signatureCount(0)
    {
        root = new TrieNode(); // Root is empty node
        cout << "[Trie] Initialized" << endl;
    }

    // Insert: Add signature character by character
    // Creates path if doesn't exist, marks end with signature data
    void insert(const Signature &sig)
    {
        if (sig.pattern.empty())
            return;

        TrieNode *current = root;

        // Build/traverse path for each character
        for (char c : sig.pattern)
        {
            // If this character path doesn't exist, create it
            if (current->children.find(c) == current->children.end())
            {
                current->children[c] = new TrieNode();
            }
            current = current->children[c]; // Move down the tree
        }

        // Mark end of this signature and store full details
        current->isEndOfWord = true;
        current->sigData = new Signature(sig);
        signatureCount++;
    }

    // Search: Check if exact pattern exists
    // Walks down tree following characters, checks if valid endpoint
    bool search(const string &pattern) const
    {
        TrieNode *current = root;

        for (char c : pattern)
        {
            if (current->children.find(c) == current->children.end())
            {
                return false; // Path broken = pattern doesn't exist
            }
            current = current->children[c];
        }

        // Path exists, but is it a complete signature?
        return current->isEndOfWord;
    }

    // Check prefix: Does any signature start with this prefix?
    // Example: "mal" would return true if "malware" is stored
    // Useful for autocomplete or pattern analysis
    bool startsWith(const string &prefix) const
    {
        TrieNode *current = root;

        for (char c : prefix)
        {
            if (current->children.find(c) == current->children.end())
            {
                return false;
            }
            current = current->children[c];
        }

        return true; // Prefix path exists (may or may not be complete word)
    }

    // Get full signature details for a pattern
    // Returns pointer (nullptr if not found)
    Signature *getSignature(const string &pattern)
    {
        TrieNode *current = root;

        // Walk the path
        for (char c : pattern)
        {
            if (current->children.find(c) == current->children.end())
            {
                return nullptr; // Path doesn't exist
            }
            current = current->children[c];
        }

        // Check if this is a valid endpoint with data
        if (current->isEndOfWord)
        {
            return current->sigData;
        }
        return nullptr;
    }

    int getSize() const
    {
        return signatureCount;
    }

    void displayStats() const
    {
        cout << "[Trie] Total signatures: " << signatureCount << endl;
        cout << "[Trie] Structure: Prefix tree" << endl;
    }

    ~Trie()
    {
        delete root; // TrieNode destructor handles recursive cleanup
    }
};

#endif