#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <string>

using namespace std;

class BloomFilter
{
private:
    vector<bool> bits;
    int size;

    int hash1(const string &key) const
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash = hash * 31 + c;
        }
        return hash % size;
    }

    int hash2(const string &key) const
    {
        unsigned long hash = 5381;
        for (char c : key)
        {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % size;
    }

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
    BloomFilter(int filterSize = 10000) : size(filterSize)
    {
        bits.resize(size, false);
    }

    void insert(const string &key)
    {
        bits[hash1(key)] = true;
        bits[hash2(key)] = true;
        bits[hash3(key)] = true;
    }

    bool mightContain(const string &key) const
    {
        return bits[hash1(key)] && bits[hash2(key)] && bits[hash3(key)];
    }

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
};

#endif