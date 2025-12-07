#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <string>
using namespace std;

// Structure to hold virus signature information
struct Signature
{
    string pattern; // Virus pattern (e.g., "malware_pattern_001")
    string name;    // Virus name (e.g., "Trojan.Win32")
    string type;    // Type: "malware", "trojan", "worm", "virus"
    int severity;   // Danger level: 1 (low) to 10 (critical)

    // Constructor for easy creation
    Signature(string p = "", string n = "", string t = "", int s = 5)
        : pattern(p), name(n), type(t), severity(s) {}
};

#endif