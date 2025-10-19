#ifndef SIGNATUREDB_H
#define SIGNATUREDB_H

#include <string>
#include "linkedlist.h"

using namespace std;

// SignatureDB - Database that stores virus signatures using a linked list
class SignatureDB {
private:
    LinkedList<string> signatures;  // Linked list to store all virus patterns
    
public:
    // Constructor
    SignatureDB();
    
    // Load virus signatures from a file
    // File should have one signature per line
    void loadSignatures(const string& filename);
    
    // Add a single signature to the database
    void addSignature(const string& signature);
    
    // Search for a signature (uses linear search from linked list)
    bool searchSignature(const string& signature) const;
    
    // Get total number of signatures in database
    int getSignatureCount() const;
    
    // Display all signatures (for debugging/demo)
    void displaySignatures() const;
    
    // Display implementation status (for D2 requirements)
    void displayImplementationStatus() const;
    
    // Get signature at specific index (for scanner to iterate through)
    string getSignatureAt(int index) const;
    
    // Destructor
    ~SignatureDB();
};

#endif