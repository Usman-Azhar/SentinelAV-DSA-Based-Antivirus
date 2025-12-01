#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "linkedlist.h"
#include "signature.h"

using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 1000;
    LinkedList<Signature> table[TABLE_SIZE];
    int itemCount;

    int hashFunction(const string& key) const {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() : itemCount(0) {}

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
        return Signature();
    }

    int getSize() const {
        return itemCount;
    }

    double getLoadFactor() const {
        return (double)itemCount / TABLE_SIZE;
    }
};

#endif