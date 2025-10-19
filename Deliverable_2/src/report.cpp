#include "report.h"
#include <iostream>

using namespace std;

void Report::bubbleSort() {
    int n = results.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Descending order: threats high to low
            if (results[j].threatsFound < results[j + 1].threatsFound) {
                ScanResult temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }
}

Report::Report() {}

void Report::addResult(const ScanResult& result) {
    results.push_back(result);
}

void Report::sortByThreatLevel() {
    cout << "[Report] Sorting using Bubble Sort (D2 Implementation)" << endl;
    bubbleSort();
    cout << "[Report] Results sorted by threat level (high to low)" << endl;
}

void Report::displayResults() const {
    cout << "\n[Report] Generating scan summary..." << endl;
    cout << "========================================" << endl;
    cout << "Total Files Scanned: " << results.size() << endl;
    
    int totalThreats = 0;
    for (const ScanResult& r : results) {
        totalThreats += r.threatsFound;
        string status = r.isInfected ? "INFECTED" : "CLEAN";
        cout << "  " << r.filename << " : " << status 
             << " (" << r.threatsFound << " threats)" << endl;
    }
    
    cout << "Total Threats: " << totalThreats << endl;
    cout << "========================================" << endl;
}

void Report::displayImplementationStatus() const {
    cout << "\n[Report] Implementation Status:" << endl;
    cout << "  D2: Vector storage - IMPLEMENTED" << endl;
    cout << "  D2: Bubble sort - IMPLEMENTED" << endl;
    cout << "  D3: Priority Queue / Heap - DECLARED (TODO)" << endl;
    cout << "  D3: File export - DECLARED (TODO)" << endl;
}

int main() {
    Report report;
    
    // Add some test data
    ScanResult file1 = {"clean.txt", 0, false};
    ScanResult file2 = {"suspicious.exe", 5, true};
    ScanResult file3 = {"malware.dll", 2, true};
    ScanResult file4 = {"document.pdf", 0, false};
    ScanResult file5 = {"virus.bin", 8, true};
    
    report.addResult(file1);
    report.addResult(file2);
    report.addResult(file3);
    report.addResult(file4);
    report.addResult(file5);
    
    cout << "=== BEFORE SORTING ===" << endl;
    report.displayResults();
    
    cout << "\n=== SORTING ===" << endl;
    report.sortByThreatLevel();
    
    cout << "\n=== AFTER SORTING ===" << endl;
    report.displayResults();
    
    cout << "\n=== IMPLEMENTATION STATUS ===" << endl;
    report.displayImplementationStatus();
    
    return 0;
}