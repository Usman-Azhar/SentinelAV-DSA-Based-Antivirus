#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

// ScanResult: Summary of scanning results for one file
// Aggregates all detections for that file into a single record
struct ScanResult
{
    string filename;  // Name of the scanned file
    int threatsFound; // Total number of threats detected in this file
    bool isInfected;  // True if any threats found, false if clean

    ScanResult(string f = "", int t = 0, bool i = false)
        : filename(f), threatsFound(t), isInfected(i) {}
};

// ThreatComparator: Custom comparison for priority queue
// Used to create MAX heap (highest threat count at top)
// Returns true if 'a' has LOWER priority than 'b' (inverted for max heap)
struct ThreatComparator
{
    bool operator()(const ScanResult &a, const ScanResult &b) const
    {
        return a.threatsFound < b.threatsFound; // Lower count = lower priority
    }
};

// Report: Generates and manages scan result reports
// Features: Sorting, top threats, file export, statistics
class Report
{
private:
    vector<ScanResult> results; // Stores all file scan results

    // Merge Sort helper functions for sorting by threat level
    void merge(vector<ScanResult> &arr, int left, int mid, int right);
    void mergeSortHelper(vector<ScanResult> &arr, int left, int right);

public:
    Report();

    void addResult(const ScanResult &result); // Add a file's scan result
    void sortByThreatLevel();                 // Sort results using merge sort (descending)
    void displayResults() const;              // Print formatted report to console

    // Priority Queue operations for finding top threats
    void buildHeap();                        // Build max heap from results
    ScanResult getMostDangerousFile() const; // Find file with most threats
    void displayTopThreats(int count) const; // Show top N most infected files

    void exportToFile(const string &filename) const; // Save report to text file
};

#endif