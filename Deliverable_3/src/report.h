#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <queue>

using namespace std;

struct ScanResult
{
    string filename;
    int threatsFound;
    bool isInfected;

    ScanResult(string f = "", int t = 0, bool i = false)
        : filename(f), threatsFound(t), isInfected(i) {}
};

struct ThreatComparator
{
    bool operator()(const ScanResult &a, const ScanResult &b) const
    {
        return a.threatsFound < b.threatsFound;
    }
};

class Report
{
private:
    vector<ScanResult> results;

    void merge(vector<ScanResult> &arr, int left, int mid, int right);
    void mergeSortHelper(vector<ScanResult> &arr, int left, int right);

public:
    Report();

    void addResult(const ScanResult &result);
    void sortByThreatLevel();
    void displayResults() const;

    void buildHeap();
    ScanResult getMostDangerousFile() const;
    void displayTopThreats(int count) const;
    void exportToFile(const string &filename) const;
};

#endif