#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "signature.h"

using namespace std;

// TrieNode - represents one character in the trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;  // Maps character -> child node
    bool isEndOfWord;                          // True if this marks end of a signature
    Signature* sigData;                        // Stores full signature data if end of word
    
    TrieNode() : isEndOfWord(false), sigData(nullptr) {}
    
    ~TrieNode() {
        if (sigData) delete sigData;
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

// Trie - Prefix tree for efficient pattern matching
class Trie {
private:
    TrieNode* root;
    int signatureCount;
    
public:
    Trie() : signatureCount(0) {
        root = new TrieNode();
        cout << "[Trie] Initialized" << endl;
    }
    
    // Insert a signature pattern into the trie
    void insert(const Signature& sig) {
        if (sig.pattern.empty()) return;
        
        TrieNode* current = root;
        
        // Traverse/create nodes for each character
        for (char c : sig.pattern) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        
        // Mark end of signature and store data
        current->isEndOfWord = true;
        current->sigData = new Signature(sig);
        signatureCount++;
    }
    
    // Search for exact pattern match
    bool search(const string& pattern) const {
        TrieNode* current = root;
        
        for (char c : pattern) {
            if (current->children.find(c) == current->children.end()) {
                return false;  // Path doesn't exist
            }
            current = current->children[c];
        }
        
        return current->isEndOfWord;  // True only if complete signature
    }
    
    // Check if pattern is a prefix of any signature
    bool startsWith(const string& prefix) const {
        TrieNode* current = root;
        
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        
        return true;  // Prefix exists
    }
    
    // Get signature details if pattern exists
    Signature* getSignature(const string& pattern) {
        TrieNode* current = root;
        
        for (char c : pattern) {
            if (current->children.find(c) == current->children.end()) {
                return nullptr;
            }
            current = current->children[c];
        }
        
        if (current->isEndOfWord) {
            return current->sigData;
        }
        return nullptr;
    }
    
    int getSize() const {
        return signatureCount;
    }
    
    void displayStats() const {
        cout << "[Trie] Total signatures: " << signatureCount << endl;
        cout << "[Trie] Structure: Prefix tree" << endl;
    }
    
    ~Trie() {
        delete root;
    }
};

#endif