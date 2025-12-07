#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// BloomFilter: Probabilistic data structure for fast membership testing
// Purpose: First-level filter to quickly eliminate non-existent patterns
// Tradeoff: Very fast but may have false positives (never false negatives)
class BloomFilter
{
private:
    vector<bool> bits; // Bit array for storing hash results
    int size;          // Total size of the bit array

    // Hash Function 1: Uses polynomial rolling hash (multiplier: 31)
    int hash1(const string &key) const
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash = hash * 31 + c;
        }
        return hash % size;
    }

    // Hash Function 2: djb2 algorithm (shift + add)
    int hash2(const string &key) const
    {
        unsigned long hash = 5381;
        for (char c : key)
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % size;
    }

    // Hash Function 3: Similar to hash1 but different multiplier (37)
    int hash3(const string &key) const
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash = hash * 37 + c;
        }
        return hash % size;
    }

public:
    // Constructor: Initialize bit array with given size
    BloomFilter(int filterSize = 10000) : size(filterSize)
    {
        bits.resize(size, false); // All bits start as false
        cout << "[BloomFilter] Initialized with size: " << size << endl;
    }

    // Insert: Set bits at 3 hash positions to true
    // Why 3 hashes? Balance between accuracy and speed
    void insert(const string &key)
    {
        bits[hash1(key)] = true;
        bits[hash2(key)] = true;
        bits[hash3(key)] = true;
    }

    // Check membership: Returns true if ALL 3 hash positions are set
    // False positive possible: Different keys might hash to same positions
    // False negative IMPOSSIBLE: If inserted, all bits will be set
    bool mightContain(const string &key) const
    {
        return bits[hash1(key)] &&
               bits[hash2(key)] &&
               bits[hash3(key)];
    }

    // Calculate how full the filter is (for monitoring efficiency)
    double getFillPercentage() const
    {
        int setBits = 0;
        for (bool bit : bits)
        {
            if (bit)
                setBits++;
        }
        return (double)setBits / size * 100.0;
    }

    // Display statistics for debugging
    void displayStats() const
    {
        cout << "[BloomFilter] Size: " << size << " bits" << endl;
        cout << "[BloomFilter] Fill: " << getFillPercentage() << "%" << endl;
        cout << "[BloomFilter] Hash functions: 3" << endl;
    }
};

#endif