#include "report.h"
#include <iostream>
#include <fstream>

using namespace std;

Report::Report() {}

void Report::addResult(const ScanResult &result)
{
    results.push_back(result);
}

void Report::merge(vector<ScanResult> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<ScanResult> leftArr(n1);
    vector<ScanResult> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i].threatsFound >= rightArr[j].threatsFound)
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void Report::mergeSortHelper(vector<ScanResult> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void Report::sortByThreatLevel()
{
    cout << "[Report] Sorting results using Merge Sort..." << endl;
    if (!results.empty())
    {
        mergeSortHelper(results, 0, results.size() - 1);
    }
    cout << "[Report] Results sorted by threat level (descending)" << endl;
}

void Report::displayResults() const
{
    cout << "\n========================================" << endl;
    cout << "         SCAN SUMMARY REPORT" << endl;
    cout << "========================================" << endl;
    cout << "Total Files Scanned: " << results.size() << endl;
    cout << "----------------------------------------" << endl;

    int totalThreats = 0;
    int infectedFiles = 0;

    for (const ScanResult &r : results)
    {
        totalThreats += r.threatsFound;
        if (r.isInfected)
            infectedFiles++;

        string status = r.isInfected ? "[INFECTED]" : "[CLEAN]   ";
        cout << status << " " << r.filename
             << " (" << r.threatsFound << " threats)" << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "Total Threats Detected: " << totalThreats << endl;
    cout << "Infected Files: " << infectedFiles << endl;
    cout << "Clean Files: " << (results.size() - infectedFiles) << endl;
    cout << "========================================" << endl;
}

void Report::buildHeap()
{
    cout << "[Report] Building priority queue (max heap)..." << endl;
    priority_queue<ScanResult, vector<ScanResult>, ThreatComparator> pq;

    for (const ScanResult &r : results)
    {
        pq.push(r);
    }

    cout << "[Report] Heap constructed with " << pq.size() << " elements" << endl;
}

ScanResult Report::getMostDangerousFile() const
{
    if (results.empty())
    {
        return ScanResult("", 0, false);
    }

    ScanResult maxThreat = results[0];
    for (const ScanResult &r : results)
    {
        if (r.threatsFound > maxThreat.threatsFound)
        {
            maxThreat = r;
        }
    }

    cout << "\n[CRITICAL] Most dangerous file: " << maxThreat.filename
         << " with " << maxThreat.threatsFound << " threats" << endl;

    return maxThreat;
}

void Report::displayTopThreats(int count) const
{
    cout << "\n========================================" << endl;
    cout << "    TOP " << count << " MOST DANGEROUS FILES" << endl;
    cout << "========================================" << endl;

    priority_queue<ScanResult, vector<ScanResult>, ThreatComparator> pq;
    for (const ScanResult &r : results)
    {
        pq.push(r);
    }

    int rank = 1;
    while (!pq.empty() && rank <= count)
    {
        ScanResult top = pq.top();
        pq.pop();

        cout << rank << ". " << top.filename
             << " - " << top.threatsFound << " threats" << endl;
        rank++;
    }
    cout << "========================================" << endl;
}

void Report::exportToFile(const string &filename) const
{
    cout << "\n[Report] Exporting report to: " << filename << endl;

    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "[Report] ERROR: Could not create export file!" << endl;
        return;
    }

    outFile << "========================================\n";
    outFile << "      SENTINELAV SCAN REPORT\n";
    outFile << "========================================\n\n";

    outFile << "Total Files Scanned: " << results.size() << "\n";
    outFile << "----------------------------------------\n";

    int totalThreats = 0;
    int infectedFiles = 0;

    for (const ScanResult &r : results)
    {
        totalThreats += r.threatsFound;
        if (r.isInfected)
            infectedFiles++;

        string status = r.isInfected ? "[INFECTED]" : "[CLEAN]   ";
        outFile << status << " " << r.filename
                << " (" << r.threatsFound << " threats)\n";
    }

    outFile << "----------------------------------------\n";
    outFile << "Total Threats Detected: " << totalThreats << "\n";
    outFile << "Infected Files: " << infectedFiles << "\n";
    outFile << "Clean Files: " << (results.size() - infectedFiles) << "\n";
    outFile << "========================================\n";

    outFile.close();
    cout << "[Report] Report exported successfully!" << endl;
}