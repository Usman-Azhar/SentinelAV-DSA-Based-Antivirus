#ifndef SIGNATUREDB_H
#define SIGNATUREDB_H

#include <string>
#include "linkedlist.h"
#include "signature.h"
#include "trie.h"
#include "hashtable.h"
#include "bloomfilter.h"

using namespace std;

// SignatureDB - Database that stores virus signatures using multiple data structures
class SignatureDB {
private:
    // D2: Keep linked list for backwards compatibility
    LinkedList<string> signatures;  
    
    // D3: NEW ADVANCED DATA STRUCTURES
    LinkedList<Signature> signatureDetails;  // Detailed signature info
    Trie signatureTrie;                      // Prefix trie for pattern matching
    HashTable hashTable;                     // Hash table for O(1) lookup
    BloomFilter bloomFilter;                 // Bloom filter for fast preliminary checks
    
public:
    // Constructor
    SignatureDB();
    
    // D2: Old methods (keep for compatibility)
    void loadSignatures(const string& filename);
    void addSignature(const string& signature);
    bool searchSignature(const string& signature) const;
    int getSignatureCount() const;
    void displaySignatures() const;
    string getSignatureAt(int index) const;
    
    // D3: NEW ADVANCED METHODS
    void loadSignaturesAdvanced(const string& filename);
    void addSignatureAdvanced(const Signature& sig);
    bool searchSignatureFast(const string& pattern) const;
    Signature* getSignatureDetails(const string& pattern);
    bool searchWithTrie(const string& pattern) const;
    
    // Display implementation status
    void displayImplementationStatus() const;
    
    // Destructor
    ~SignatureDB();
};

#endif