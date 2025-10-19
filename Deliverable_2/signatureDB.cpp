#include "signatureDB.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor - initializes an empty database
SignatureDB::SignatureDB() {
    cout << "[SignatureDB] Database initialized (using Linked List)" << endl;
}

// Load virus signatures from a text file
void SignatureDB::loadSignatures(const string& filename) {
    cout << "[SignatureDB] Loading signatures from: " << filename << endl;
    
    ifstream file(filename);
    
    // Check if file opened successfully
    if (!file.is_open()) {
        cout << "[SignatureDB] ERROR: Could not open file!" << endl;
        return;
    }
    
    string line;
    int count = 0;
    
    // Read file line by line
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        
        // Add signature to linked list
        signatures.insert(line);
        count++;
    }
    
    file.close();
    cout << "[SignatureDB] Loaded " << count << " signatures successfully" << endl;
}

// Add a single signature to the database
void SignatureDB::addSignature(const string& signature) {
    if (signature.empty()) {
        cout << "[SignatureDB] Warning: Empty signature not added" << endl;
        return;
    }
    signatures.insert(signature);
    cout << "[SignatureDB] Added signature: " << signature << endl;
}

// Search for a signature using linear search
bool SignatureDB::searchSignature(const string& signature) const {
    cout << "[SignatureDB] Searching for: '" << signature << "'" << endl;
    
    // Use the linked list's search function (linear search)
    bool found = signatures.search(signature);
    
    // Alternative: can also use recursive search
    // bool found = signatures.searchRecursive(signature);
    
    return found;
}

// Get the total number of signatures
int SignatureDB::getSignatureCount() const {
    return signatures.getSize();
}

// Display all signatures (useful for debugging)
void SignatureDB::displaySignatures() const {
    cout << "\n[SignatureDB] All Signatures:" << endl;
    signatures.display();
}

// Display what's implemented for D2
void SignatureDB::displayImplementationStatus() const {
    cout << "\n[SignatureDB] Implementation Status:" << endl;
    cout << "  D2: Linked List storage - IMPLEMENTED" << endl;
    cout << "  D2: Linear search - IMPLEMENTED" << endl;
    cout << "  D2: Recursive search - IMPLEMENTED" << endl;
    cout << "  D3: Trie structure - DECLARED (TODO)" << endl;
    cout << "  D3: Aho-Corasick automaton - DECLARED (TODO)" << endl;
    cout << "  D3: Hash table - DECLARED (TODO)" << endl;
    cout << "  D3: Bloom filter - DECLARED (TODO)" << endl;
}

// Get signature at a specific position (for iteration)
string SignatureDB::getSignatureAt(int index) const {
    return signatures.getAt(index);
}

// Destructor
SignatureDB::~SignatureDB() {
    // LinkedList destructor will automatically clean up
    cout << "[SignatureDB] Database closed" << endl;
}