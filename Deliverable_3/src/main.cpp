#include <iostream>
#include <vector>
#include "signatureDB.h"
#include "scanner.h"
#include "report.h"

using namespace std;

int main()
{
    cout << "=================================" << endl;
    cout << "   SentinelAV - Deliverable 3" << endl;
    cout << "   Real File Scanning Demo" << endl;
    cout << "=================================" << endl
         << endl;

    // PART 1: Load virus database using ADVANCED method
    cout << "========== PART 1: LOADING VIRUS DATABASE ==========" << endl;
    SignatureDB sigDB;

    sigDB.loadSignaturesAdvanced("../data/virus_signatures.txt");

    cout << "\nTotal signatures loaded: " << sigDB.getSignatureCount() << endl;
    // sigDB.displayImplementationStatus();
    cout << endl;

    // PART 2: Prepare scanner and report
    Scanner scanner;
    Report report;

    // PART 3: List of ACTUAL FILES to scan
    vector<string> filesToScan = {
        "../data/sample_input.txt",
        "../data/infected_document.txt",
        "../data/suspicious_email.txt",
        "../data/clean_file.txt",
        "../data/heavily_infected.txt"};

    cout << "========== PART 2: SCANNING FILES ==========" << endl;
    cout << "Files to scan: " << filesToScan.size() << endl
         << endl;

    // PART 4: Scan each ACTUAL file
    for (const string &filename : filesToScan)
    {
        scanner.scanFile(filename, sigDB);

        int threatsFound = scanner.getLastFileThreatCount();
        bool isInfected = (threatsFound > 0);

        size_t lastSlash = filename.find_last_of("/\\");
        string shortName = (lastSlash != string::npos)
                               ? filename.substr(lastSlash + 1)
                               : filename;

        report.addResult(ScanResult{shortName, threatsFound, isInfected});

        cout << "---" << endl;
    }

    // scanner.displayImplementationStatus();
    cout << endl;

    // PART 5: Generate and display report
    cout << "========== PART 3: GENERATING REPORT ==========" << endl;
    report.sortByThreatLevel();
    report.displayResults();

    // PART 6: Export report to file
    cout << "\n========== PART 4: EXPORTING REPORT ==========" << endl;
    report.exportToFile("../docs/scan_report.txt");

    // PART 7: Display top threats using priority queue
    cout << "\n========== PART 5: TOP THREATS ANALYSIS ==========" << endl;
    report.getMostDangerousFile();
    report.displayTopThreats(3);

    // report.displayImplementationStatus();

    // Final summary
    cout << "\n=================================" << endl;
    cout << "  ALL SCANS COMPLETE!" << endl;
    cout << "=================================" << endl;

    cout << "\nD3 Features Demonstrated:" << endl;
    cout << "  Real file scanning (NOT hardcoded)" << endl;
    cout << "  Prefix Trie for pattern storage" << endl;
    cout << "  Hash Table for fast lookup" << endl;
    cout << "  Bloom Filter for efficiency" << endl;
    cout << "  Queue for detection results" << endl;
    cout << "  Merge sort for ranking" << endl;
    cout << "  Priority Queue for top threats" << endl;
    cout << "  Report export to file" << endl;

    return 0;
}