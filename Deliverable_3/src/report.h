#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>

using namespace std;

struct ScanResult {
    string filename; // Name of the scanned file
    int threatsFound; // Number of threats found in the file
    bool isInfected; // Infection status of the file
};

class Report {
private:
    vector<ScanResult> results;
    
    // IMPLEMENTED: Bubble sort for sorting results by threat level
    void bubbleSort();

public:
    Report();
    void addResult(const ScanResult& result);
    
    // IMPLEMENTED: Sorting
    void sortByThreatLevel();
    void displayResults() const;
    
    // TODO D3: Use Priority Queue / Heap for ranking
    // priority_queue<ScanResult> rankedResults;
    // void buildHeap();
    // ScanResult getMostDangerousFile();
    
    // TODO D3: Export to file
    // void exportReportToFile(const string& filename);
    
    void displayImplementationStatus() const;
};

#endif