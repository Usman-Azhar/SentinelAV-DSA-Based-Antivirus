#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "linkedlist.h"
#include "signature.h"

using namespace std;

// HashTable: Fast O(1) lookup using hash function + chaining for collisions
// Structure: Array of LinkedLists (each bucket is a linked list)
// Purpose: Quick signature verification after Bloom Filter check
class HashTable
{
private:
    static const int TABLE_SIZE = 1000;      // Fixed size hash table
    LinkedList<Signature> table[TABLE_SIZE]; // Each bucket stores colliding signatures
    int itemCount;                           // Total signatures stored across all buckets

    // Hash Function: djb2 algorithm - converts pattern string to table index
    // Same algorithm as BloomFilter's hash2 for consistency
    int hashFunction(const string &key) const
    {
        unsigned long hash = 5381;
        for (char c : key)
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % TABLE_SIZE; // Map to valid index [0, TABLE_SIZE-1]
    }

public:
    HashTable() : itemCount(0)
    {
        cout << "[HashTable] Initialized with size: " << TABLE_SIZE << endl;
    }

    // Insert: Add signature to appropriate bucket
    // Collision handling: Chaining (append to linked list at that index)
    void insert(const Signature &sig)
    {
        int index = hashFunction(sig.pattern);
        table[index].insert(sig); // Add to linked list at this bucket
        itemCount++;
    }

    // Search: Check if pattern exists in the table
    // Process: Hash → Find bucket → Linear search within that bucket's list
    bool search(const string &pattern) const
    {
        int index = hashFunction(pattern);
        // Iterate through linked list at this bucket
        for (int i = 0; i < table[index].getSize(); i++)
        {
            if (table[index].getAt(i).pattern == pattern)
            {
                return true; // Found!
            }
        }
        return false; // Not in this bucket
    }

    // Get full signature details (not just pattern string)
    // Returns pointer to allow nullptr when not found
    Signature *getSignature(const string &pattern)
    {
        int index = hashFunction(pattern);
        for (int i = 0; i < table[index].getSize(); i++)
        {
            if (table[index].getAt(i).pattern == pattern)
            {
                static Signature temp = table[index].getAt(i);
                return &temp; // Return pointer to signature details
            }
        }
        return nullptr; // Not found
    }

    int getSize() const
    {
        return itemCount;
    }

    // Statistics: Analyze hash table performance
    void displayStats() const
    {
        cout << "[HashTable] Total items: " << itemCount << endl;
        cout << "[HashTable] Table size: " << TABLE_SIZE << endl;
        cout << "[HashTable] Load factor: "
             << (float)itemCount / TABLE_SIZE << endl;

        // Collision analysis: Count occupied buckets and longest chain
        int occupiedBuckets = 0;
        int maxChainLength = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            int bucketSize = table[i].getSize();
            if (bucketSize > 0)
            {
                occupiedBuckets++;
                if (bucketSize > maxChainLength)
                {
                    maxChainLength = bucketSize;
                }
            }
        }
        cout << "[HashTable] Occupied buckets: " << occupiedBuckets << endl;
        cout << "[HashTable] Max chain length: " << maxChainLength << endl;
    }
};

#endif