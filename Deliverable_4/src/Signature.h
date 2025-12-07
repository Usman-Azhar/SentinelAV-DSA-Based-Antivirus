#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <string>
using namespace std;

// Signature struct: Stores complete information about a virus pattern
// Used by: Trie, HashTable, LinkedList<Signature> for detailed storage
struct Signature
{
    string pattern; // The actual virus string to search for (e.g., "malware_pattern_001")
    string name;    // Human-readable virus name (e.g., "Trojan.Win32")
    string type;    // Category: "malware", "trojan", "worm", "virus"
    int severity;   // Danger level: 1 (low) to 10 (critical)

    // Constructor with default values for easy object creation
    Signature(string p = "", string n = "", string t = "", int s = 5)
        : pattern(p), name(n), type(t), severity(s) {}
};

#endif