#include <iostream>
#include "signatureDB.h"
#include "scanner.h"
#include "report.h"

using namespace std;

int main() {
    cout << "=================================" << endl;
    cout << "SentinelAV - Deliverable 2" << endl;
    cout << "Skeleton with DSA Implementation Plan" << endl;
    cout << "=================================" << endl << endl;
    
    // ===== DEMO 1: IMPLEMENTED - Linked Lists & Pointers (Week 1-2, 4-5) =====
    cout << "[DEMO 1] IMPLEMENTED: Linked Lists + Pointers (Week 4-5)" << endl;
    cout << "---" << endl;
    SignatureDB sigDB;
    sigDB.loadSignatures("data/virus_signatures.txt");
    sigDB.displayImplementationStatus();
    cout << endl;
    
    // ===== DEMO 2: IMPLEMENTED - Linear Search & Recursion (Week 4, 7) =====
    cout << "[DEMO 2] IMPLEMENTED: Linear Search + Recursion (Week 4 + 7)" << endl;
    cout << "---" << endl;
    string testPattern = "malware_pattern_001";
    bool found = sigDB.searchSignature(testPattern);
    cout << "Searching for '" << testPattern << "': " << (found ? "FOUND" : "NOT FOUND") << endl;
    cout << "Total signatures: " << sigDB.getSignatureCount() << endl << endl;
    
    // ===== DEMO 3: IMPLEMENTED - Queues (Week 6) =====
    cout << "[DEMO 3] IMPLEMENTED: Queues (Week 6)" << endl;
    cout << "---" << endl;
    Scanner scanner;
    scanner.scanFile("data/sample_input.txt", sigDB);
    scanner.displayImplementationStatus();
    cout << endl;
    
    // ===== DEMO 4: IMPLEMENTED - Sorting (Week 8) =====
    cout << "[DEMO 4] IMPLEMENTED: Sorting - Bubble Sort (Week 8)" << endl;
    cout << "---" << endl;
    
    Report report;
    report.addResult({"sample_input.txt", 0, false});
    report.addResult({"test_file_1.txt", 3, true});
    report.addResult({"test_file_2.txt", 1, true});
    
    report.sortByThreatLevel();
    report.displayResults();
    report.displayImplementationStatus();
    
    cout << endl << "=================================" << endl;
    cout << "D2 SKELETON COMPLETE" << endl;
    cout << "=================================" << endl;
    cout << "\nD2 IMPLEMENTED (Week 1-8):" << endl;
    cout << "  ✓ Pointers (Week 1-2)" << endl;
    cout << "  ✓ Linked Lists (Week 4-5)" << endl;
    cout << "  ✓ Linear Search (Week 4)" << endl;
    cout << "  ✓ Recursion (Week 7)" << endl;
    cout << "  ✓ Queues (Week 6)" << endl;
    cout << "  ✓ Sorting / Bubble Sort (Week 8)" << endl;
    
    cout << "\nD3+ DECLARED (TODO):" << endl;
    cout << "  ⧗ Trie (Week 10)" << endl;
    cout << "  ⧗ Aho-Corasick Automaton (Week 10 + 13-14)" << endl;
    cout << "  ⧗ Hash Table (Week 13-14)" << endl;
    cout << "  ⧗ Bloom Filter (Week 13-14)" << endl;
    cout << "  ⧗ Priority Queue / Heap (Week 15)" << endl;
    
    return 0;
}