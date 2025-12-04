#include "signatureDB.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor - initializes an empty database
SignatureDB::SignatureDB() {
    cout << "[SignatureDB] Database initialized" << endl;
    cout << "[SignatureDB] Using: Trie + Hash Table + Bloom Filter" << endl;
}

// D2: Load virus signatures from a text file (old method)
void SignatureDB::loadSignatures(const string& filename) {
    cout << "[SignatureDB] Loading signatures (D2 method): " << filename << endl;
    
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "[SignatureDB] ERROR: Could not open file!" << endl;
        return;
    }
    
    string line;
    int count = 0;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        signatures.insert(line);
        count++;
    }
    
    file.close();
    cout << "[SignatureDB] Loaded " << count << " signatures (linked list)" << endl;
}

// D2: Add a single signature (old method)
void SignatureDB::addSignature(const string& signature) {
    if (signature.empty()) {
        cout << "[SignatureDB] Warning: Empty signature not added" << endl;
        return;
    }
    signatures.insert(signature);
}

// D2: Search for a signature using linear search (old method)
bool SignatureDB::searchSignature(const string& signature) const {
    return signatures.search(signature);
}

// Get the total number of signatures
int SignatureDB::getSignatureCount() const {
    return signatures.getSize();
}

// Display all signatures
void SignatureDB::displaySignatures() const {
    cout << "\n[SignatureDB] All Signatures:" << endl;
    signatures.display();
}

// Get signature at a specific position
string SignatureDB::getSignatureAt(int index) const {
    return signatures.getAt(index);
}

// ========== D3: NEW ADVANCED METHODS ==========

// D3: Load signatures with full metadata into all data structures
void SignatureDB::loadSignaturesAdvanced(const string& filename) {
    cout << "\n[SignatureDB] Loading ADVANCED signatures..." << endl;
    cout << "[SignatureDB] File: " << filename << endl;
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[SignatureDB] ERROR: Could not open file!" << endl;
        return;
    }
    
    string line;
    int count = 0;
    
    cout << "[SignatureDB] Processing signatures..." << endl;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        // Create signature with pattern
        // You can enhance this to parse type/severity from file if needed
        Signature sig(line, "Unknown Virus", "generic", 5);
        
        // Add to ALL data structures
        addSignatureAdvanced(sig);
        count++;
        
        // Progress indicator every 5 signatures
        if (count % 5 == 0) {
            cout << "  [SignatureDB] Loaded " << count << " signatures..." << endl;
        }
    }
    
    file.close();
    
    cout << "\n[SignatureDB] ✓ Successfully loaded " << count << " signatures" << endl;
    cout << "[SignatureDB] All data structures populated:" << endl;
    
    // Display statistics for each structure
    cout << "\n--- Data Structure Statistics ---" << endl;
    signatureTrie.displayStats();
    bloomFilter.displayStats();
    hashTable.displayStats();
    cout << "--------------------------------" << endl;
}

// D3: Add signature to ALL advanced data structures
void SignatureDB::addSignatureAdvanced(const Signature& sig) {
    if (sig.pattern.empty()) return;
    
    // Add to old linked list for compatibility
    signatures.insert(sig.pattern);
    
    // Add to new D3 structures
    signatureDetails.insert(sig);      // Detailed info list
    signatureTrie.insert(sig);         // Trie for pattern matching
    bloomFilter.insert(sig.pattern);   // Bloom filter for speed
    hashTable.insert(sig);             // Hash table for O(1) access
}

// D3: Ultra-fast search using Bloom Filter -> Hash Table -> Trie
bool SignatureDB::searchSignatureFast(const string& pattern) const {
    // Step 1: Bloom filter (fastest, may have false positives)
    if (!bloomFilter.mightContain(pattern)) {
        return false;  // Definitely not in database
    }
    
    // Step 2: Hash table confirmation (O(1) average)
    if (hashTable.search(pattern)) {
        return true;
    }
    
    // Step 3: Trie confirmation (O(m) where m = pattern length)
    return signatureTrie.search(pattern);
}

// D3: Get full signature details
Signature* SignatureDB::getSignatureDetails(const string& pattern) {
    // Try hash table first (fastest)
    Signature sig = hashTable.getSignature(pattern);
    if (!sig.pattern.empty()) {
        static Signature result = sig;
        return &result;
    }
    
    // Try trie as backup
    return signatureTrie.getSignature(pattern);
}

// D3: Search specifically using Trie
bool SignatureDB::searchWithTrie(const string& pattern) const {
    return signatureTrie.search(pattern);
}

// Display what's implemented
void SignatureDB::displayImplementationStatus() const {
    cout << "\n[SignatureDB] Implementation Status:" << endl;
    cout << "  ✓ D2: Linked List - IMPLEMENTED" << endl;
    cout << "  ✓ D2: Linear Search - IMPLEMENTED" << endl;
    cout << "  ✓ D3: Prefix Trie - IMPLEMENTED" << endl;
    cout << "  ✓ D3: Hash Table - IMPLEMENTED" << endl;
    cout << "  ✓ D3: Bloom Filter - IMPLEMENTED" << endl;
    cout << "  ✓ D3: Signature Metadata - IMPLEMENTED" << endl;
}

// Destructor
SignatureDB::~SignatureDB() {
    cout << "[SignatureDB] Database closed" << endl;
}