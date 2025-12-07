#include "signatureDB.h"
#include <iostream>
#include <fstream>

using namespace std;

// Initialize empty database with all data structures
SignatureDB::SignatureDB()
{
    cout << "[SignatureDB] Database initialized" << endl;
    cout << "[SignatureDB] Using: Trie + Hash Table + Bloom Filter" << endl;
}

// ========== D2 METHODS (Legacy - Simple LinkedList only) ==========

// D2: Basic loading - just stores pattern strings in linked list
void SignatureDB::loadSignatures(const string &filename)
{
    cout << "[SignatureDB] Loading signatures (D2 method): " << filename << endl;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "[SignatureDB] ERROR: Could not open file!" << endl;
        return;
    }

    string line;
    int count = 0;

    // Read each line and add to linked list
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        signatures.insert(line); // O(n) insertion at end
        count++;
    }

    file.close();
    cout << "[SignatureDB] Loaded " << count << " signatures (linked list)" << endl;
}

// D2: Simple add - just pattern string
void SignatureDB::addSignature(const string &signature)
{
    if (signature.empty())
    {
        cout << "[SignatureDB] Warning: Empty signature not added" << endl;
        return;
    }
    signatures.insert(signature);
}

// D2: Linear search through linked list - O(n)
bool SignatureDB::searchSignature(const string &signature) const
{
    return signatures.search(signature);
}

int SignatureDB::getSignatureCount() const
{
    return signatures.getSize();
}

void SignatureDB::displaySignatures() const
{
    cout << "\n[SignatureDB] All Signatures:" << endl;
    signatures.display();
}

// Get signature at index - needed for scanner iteration
string SignatureDB::getSignatureAt(int index) const
{
    return signatures.getAt(index);
}

// ========== D3 METHODS (Advanced - Multiple Data Structures) ==========

// D3: Advanced loading - populates ALL data structures simultaneously
// Process: Read file → Create Signature objects → Add to all structures
void SignatureDB::loadSignaturesAdvanced(const string &filename)
{
    cout << "\n[SignatureDB] Loading ADVANCED signatures..." << endl;
    cout << "[SignatureDB] File: " << filename << endl;

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "[SignatureDB] ERROR: Could not open file!" << endl;
        return;
    }

    string line;
    int count = 0;

    cout << "[SignatureDB] Processing signatures..." << endl;

    // Read and process each signature
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        // Create full Signature object with metadata
        // In a real system, you'd parse type/severity from file
        Signature sig(line, "Unknown Virus", "generic", 5);

        // Add to ALL data structures for multi-layer search
        addSignatureAdvanced(sig);
        count++;

        // Progress indicator
        if (count % 5 == 0)
        {
            cout << "[SignatureDB] Loaded " << count << " signatures..." << endl;
        }
    }

    file.close();

    cout << "\n[SignatureDB] Successfully loaded " << count << " signatures" << endl;
    cout << "[SignatureDB] All data structures populated:" << endl;
}

// D3: Add single signature to ALL data structures
// Multi-structure storage enables different search strategies
void SignatureDB::addSignatureAdvanced(const Signature &sig)
{
    if (sig.pattern.empty())
        return;

    // Add to legacy structure (D2 compatibility)
    signatures.insert(sig.pattern);

    // Add to advanced structures (D3)
    signatureDetails.insert(sig);    // Full metadata storage
    signatureTrie.insert(sig);       // Prefix tree - O(m) search
    bloomFilter.insert(sig.pattern); // Probabilistic filter - O(1) check
    hashTable.insert(sig);           // Hash table - O(1) average search
}

// D3: Multi-layer search strategy for optimal performance
// Layer 1: BloomFilter (fastest, eliminates non-existent)
// Layer 2: HashTable (fast confirmation)
// Layer 3: Trie (fallback pattern matching)
bool SignatureDB::searchSignatureFast(const string &pattern) const
{
    // LAYER 1: Bloom filter - ultra-fast preliminary check
    // If returns false, pattern DEFINITELY not in database
    if (!bloomFilter.mightContain(pattern))
    {
        return false; // Quick rejection - O(1)
    }

    // LAYER 2: Hash table confirmation
    // Bloom filter said "maybe", now confirm with hash table
    if (hashTable.search(pattern))
    {
        return true; // Confirmed present - O(1) average
    }

    // LAYER 3: Trie fallback (in case of hash collision)
    // Final verification using pattern matching
    return signatureTrie.search(pattern); // O(m) where m = pattern length
}

// Get complete signature details (name, type, severity)
Signature *SignatureDB::getSignatureDetails(const string &pattern)
{
    // Try hash table first (fastest lookup)
    Signature *sig = hashTable.getSignature(pattern);

    if (sig != nullptr && !sig->pattern.empty())
    {
        return sig;
    }

    // Fallback to trie if hash table didn't have it
    return signatureTrie.getSignature(pattern);
}

// Direct trie search (for testing/demonstration)
bool SignatureDB::searchWithTrie(const string &pattern) const
{
    return signatureTrie.search(pattern);
}

// Display which DSA features are implemented
void SignatureDB::displayImplementationStatus() const
{
    cout << "\n[SignatureDB] Implementation Status:" << endl;
    cout << "  D2: Linked List - IMPLEMENTED" << endl;
    cout << "  D2: Linear Search - IMPLEMENTED" << endl;
    cout << "  D3: Prefix Trie - IMPLEMENTED" << endl;
    cout << "  D3: Hash Table - IMPLEMENTED" << endl;
    cout << "  D3: Bloom Filter - IMPLEMENTED" << endl;
    cout << "  D3: Signature Metadata - IMPLEMENTED" << endl;
}

SignatureDB::~SignatureDB()
{
    cout << "[SignatureDB] Database closed" << endl;
}