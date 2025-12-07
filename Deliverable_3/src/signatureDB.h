#ifndef SIGNATUREDB_H
#define SIGNATUREDB_H

#include <string>
#include "linkedlist.h"
#include "Signature.h"
#include "trie.h"
#include "hashtable.h"
#include "bloomfilter.h"

using namespace std;

// SignatureDB: Central virus signature database using multiple data structures
// Architecture: Multi-layered search for optimal performance
// Layer 1: BloomFilter (ultra-fast rejection of non-existent patterns)
// Layer 2: HashTable (O(1) average confirmation)
// Layer 3: Trie (O(m) pattern-based search)
// Layer 4: LinkedList (legacy D2 support + detailed storage)
class SignatureDB
{
private:
    // D2: Original simple storage (kept for backward compatibility)
    LinkedList<string> signatures; // Just stores pattern strings

    // D3: Advanced multi-structure approach
    LinkedList<Signature> signatureDetails; // Stores complete Signature objects
    Trie signatureTrie;                     // Prefix tree for pattern matching
    HashTable hashTable;                    // Fast hash-based lookup
    BloomFilter bloomFilter;                // Probabilistic filter for speed

public:
    SignatureDB();

    // ========== D2 METHODS (Legacy) ==========
    // Basic functionality using only LinkedList
    void loadSignatures(const string &filename);         // Load patterns from file
    void addSignature(const string &signature);          // Add single pattern string
    bool searchSignature(const string &signature) const; // Linear search O(n)
    int getSignatureCount() const;                       // Total signatures loaded
    void displaySignatures() const;                      // Print all signatures
    string getSignatureAt(int index) const;              // Get pattern by index

    // ========== D3 METHODS (Advanced) ==========
    // Enhanced functionality using all data structures
    void loadSignaturesAdvanced(const string &filename); // Load into all structures
    void addSignatureAdvanced(const Signature &sig);     // Add to all structures

    // Multi-layer search strategy:
    // 1. Check BloomFilter (fast rejection)
    // 2. Confirm with HashTable (fast positive)
    // 3. Fallback to Trie if needed
    bool searchSignatureFast(const string &pattern) const;

    Signature *getSignatureDetails(const string &pattern); // Get full signature info
    bool searchWithTrie(const string &pattern) const;      // Trie-specific search

    void displayImplementationStatus() const; // Show which features are active

    ~SignatureDB();
};

#endif