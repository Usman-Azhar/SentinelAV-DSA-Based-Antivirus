#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "linkedlist.h"
#include "signature.h"

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 1000;
    LinkedList<Signature> table[TABLE_SIZE];
    int itemCount;
    
    // Hash function - converts string to index
    int hashFunction(const string& key) const {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TABLE_SIZE;
    }
    
public:
    HashTable() : itemCount(0) {
        cout << "[HashTable] Initialized with size: " << TABLE_SIZE << endl;
    }
    
    void insert(const Signature& sig) {
        int index = hashFunction(sig.pattern);
        table[index].insert(sig);
        itemCount++;
    }
    
    bool search(const string& pattern) const {
        int index = hashFunction(pattern);
        for (int i = 0; i < table[index].getSize(); i++) {
            if (table[index].getAt(i).pattern == pattern) {
                return true;
            }
        }
        return false;
    }
    
    Signature getSignature(const string& pattern) const {
        int index = hashFunction(pattern);
        for (int i = 0; i < table[index].getSize(); i++) {
            if (table[index].getAt(i).pattern == pattern) {
                return table[index].getAt(i);
            }
        }
        return Signature();  // Return empty signature if not found
    }
    
    int getSize() const { 
        return itemCount; 
    }
    
    void displayStats() const {
        cout << "[HashTable] Total items: " << itemCount << endl;
        cout << "[HashTable] Table size: " << TABLE_SIZE << endl;
        cout << "[HashTable] Load factor: " 
             << (float)itemCount / TABLE_SIZE << endl;
        
        // Calculate collisions
        int occupiedBuckets = 0;
        int maxChainLength = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            int bucketSize = table[i].getSize();
            if (bucketSize > 0) {
                occupiedBuckets++;
                if (bucketSize > maxChainLength) {
                    maxChainLength = bucketSize;
                }
            }
        }
        cout << "[HashTable] Occupied buckets: " << occupiedBuckets << endl;
        cout << "[HashTable] Max chain length: " << maxChainLength << endl;
    }
};

#endif