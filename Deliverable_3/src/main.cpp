#include <iostream>
#include <vector>
#include "signatureDB.h"
#include "scanner.h"
#include "report.h"

using namespace std;

// Main execution flow demonstrating all DSA concepts:
// 1. Load virus database (Trie, HashTable, BloomFilter)
// 2. Scan files for viruses (Queue for results)
// 3. Generate report (MergeSort for ranking)
// 4. Analyze top threats (Priority Queue)
int main()
{
    cout << "=================================" << endl;
    cout << "   SentinelAV - Deliverable 3" << endl;
    cout << "       Real File Scanning    " << endl;
    cout << "=================================" << endl
         << endl;

    // ========== STEP 1: LOAD VIRUS DATABASE ==========
    // Creates Trie, HashTable, and BloomFilter structures
    cout << "========== PART 1: LOADING VIRUS DATABASE ==========" << endl;
    SignatureDB sigDB;

    // Load from virus_signatures.txt into all data structures
    sigDB.loadSignaturesAdvanced("../data/virus_signatures.txt");

    cout << "\nTotal signatures loaded: " << sigDB.getSignatureCount() << endl;
    cout << endl;

    // ========== STEP 2: INITIALIZE SCANNER & REPORT ==========
    Scanner scanner; // Handles file scanning and uses Queue for detections
    Report report;   // Manages results and uses MergeSort + Priority Queue

    // List of actual files to scan (mix of clean and infected)
    vector<string> filesToScan = {
        "../data/sample_input.txt",      // Few threats
        "../data/infected_document.txt", // Medium infection
        "../data/suspicious_email.txt",  // Multiple threats
        "../data/clean_file.txt",        // No threats
        "../data/heavily_infected.txt"   // Heavily infected
    };

    cout << "========== PART 2: SCANNING FILES ==========" << endl;
    cout << "Files to scan: " << filesToScan.size() << endl
         << endl;

    // ========== STEP 3: SCAN EACH FILE ==========
    // For each file: Open → Read lines → Check signatures → Queue results
    for (const string &filename : filesToScan)
    {
        scanner.scanFile(filename, sigDB);

        // Get results from last scan
        int threatsFound = scanner.getLastFileThreatCount();
        bool isInfected = (threatsFound > 0);

        // Extract just the filename (remove path)
        size_t lastSlash = filename.find_last_of("/\\");
        string shortName = (lastSlash != string::npos)
                               ? filename.substr(lastSlash + 1)
                               : filename;

        // Add this file's results to the report
        report.addResult(ScanResult{shortName, threatsFound, isInfected});

        cout << "---" << endl;
    }

    cout << endl;

    // ========== STEP 4: GENERATE REPORT ==========
    // Uses Merge Sort to rank files by threat level (high to low)
    cout << "========== PART 3: GENERATING REPORT ==========" << endl;
    report.sortByThreatLevel(); // Merge sort algorithm - O(n log n)
    report.displayResults();    // Shows sorted results

    // ========== STEP 5: EXPORT TO FILE ==========
    cout << "\n========== PART 4: EXPORTING REPORT ==========" << endl;
    report.exportToFile("../docs/scan_report.txt");

    // ========== STEP 6: TOP THREATS ANALYSIS ==========
    // Uses Priority Queue (Max Heap) to find most dangerous files
    cout << "\n========== PART 5: TOP THREATS ANALYSIS ==========" << endl;
    report.getMostDangerousFile(); // Find single worst file
    report.displayTopThreats(3);   // Show top 3 most infected files

    // ========== FINAL SUMMARY ==========
    cout << "\n=================================" << endl;
    cout << "  ALL SCANS COMPLETE!" << endl;
    cout << "=================================" << endl;

    // List all DSA concepts demonstrated
    cout << "\nD3 Features Demonstrated:" << endl;
    cout << "  Real file scanning" << endl;
    cout << "  Prefix Trie for pattern storage" << endl;
    cout << "  Hash Table for fast lookup" << endl;
    cout << "  Bloom Filter for efficiency" << endl;
    cout << "  Queue for detection results" << endl;
    cout << "  Merge sort for ranking" << endl;
    cout << "  Priority Queue for top threats" << endl;
    cout << "  Report export to file" << endl;

    return 0;
}