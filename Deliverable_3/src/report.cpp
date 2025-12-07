#include "report.h"
#include <iostream>
#include <fstream>

using namespace std;

Report::Report() {}

// Add a file's scan result to the report
void Report::addResult(const ScanResult &result)
{
    results.push_back(result);
}

// Merge helper for merge sort algorithm
// Merges two sorted subarrays into one sorted array
// Sorting criteria: Higher threat count comes first (descending order)
void Report::merge(vector<ScanResult> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temporary arrays for merging
    vector<ScanResult> leftArr(n1);
    vector<ScanResult> rightArr(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        // Compare threat counts - higher goes first (descending)
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

    // Copy remaining elements from left array (if any)
    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements from right array (if any)
    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Recursive merge sort implementation
// Divides array into halves, sorts them, then merges
// Time complexity: O(n log n)
void Report::mergeSortHelper(vector<ScanResult> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2; // Find middle point

        // Sort first and second halves recursively
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Public interface for sorting - sorts by threat level (descending)
void Report::sortByThreatLevel()
{
    cout << "[Report] Sorting results using Merge Sort..." << endl;
    if (!results.empty())
    {
        mergeSortHelper(results, 0, results.size() - 1);
    }
    cout << "[Report] Results sorted by threat level (descending)" << endl;
}

// Display formatted report to console
void Report::displayResults() const
{
    cout << "\n========================================" << endl;
    cout << "         SCAN SUMMARY REPORT" << endl;
    cout << "========================================" << endl;
    cout << "Total Files Scanned: " << results.size() << endl;
    cout << "----------------------------------------" << endl;

    int totalThreats = 0;
    int infectedFiles = 0;

    // Display each file's status
    for (const ScanResult &r : results)
    {
        totalThreats += r.threatsFound;
        if (r.isInfected)
            infectedFiles++;

        string status = r.isInfected ? "[INFECTED]" : "[CLEAN]   ";
        cout << status << " " << r.filename
             << " (" << r.threatsFound << " threats)" << endl;
    }

    // Summary statistics
    cout << "----------------------------------------" << endl;
    cout << "Total Threats Detected: " << totalThreats << endl;
    cout << "Infected Files: " << infectedFiles << endl;
    cout << "Clean Files: " << (results.size() - infectedFiles) << endl;
    cout << "========================================" << endl;
}

// Build max heap from results (demonstration of heap concept)
void Report::buildHeap()
{
    cout << "[Report] Building priority queue (max heap)..." << endl;
    priority_queue<ScanResult, vector<ScanResult>, ThreatComparator> pq;

    // Add all results to priority queue
    for (const ScanResult &r : results)
    {
        pq.push(r); // Automatically maintains heap property
    }

    cout << "[Report] Heap constructed with " << pq.size() << " elements" << endl;
}

// Find the file with most threats using linear search
// Alternative: Could use priority queue for O(1) access to max
ScanResult Report::getMostDangerousFile() const
{
    if (results.empty())
    {
        return ScanResult("", 0, false);
    }

    // Linear search for maximum
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

// Display top N most dangerous files using Priority Queue (Max Heap)
// Priority Queue automatically orders elements by threat count
void Report::displayTopThreats(int count) const
{
    cout << "\n========================================" << endl;
    cout << "    TOP " << count << " MOST DANGEROUS FILES" << endl;
    cout << "========================================" << endl;

    // Create max heap - highest threat count at top
    priority_queue<ScanResult, vector<ScanResult>, ThreatComparator> pq;
    for (const ScanResult &r : results)
    {
        pq.push(r); // O(log n) insertion
    }

    // Extract top N elements
    int rank = 1;
    while (!pq.empty() && rank <= count)
    {
        ScanResult top = pq.top(); // O(1) access to max
        pq.pop();                  // O(log n) removal

        cout << rank << ". " << top.filename
             << " - " << top.threatsFound << " threats" << endl;
        rank++;
    }
    cout << "========================================" << endl;
}

// Export report to text file for permanent record
void Report::exportToFile(const string &filename) const
{
    cout << "\n[Report] Exporting report to: " << filename << endl;

    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cout << "[Report] ERROR: Could not create export file!" << endl;
        return;
    }

    // Write header
    outFile << "========================================\n";
    outFile << "      SENTINELAV SCAN REPORT\n";
    outFile << "========================================\n\n";

    outFile << "Total Files Scanned: " << results.size() << "\n";
    outFile << "----------------------------------------\n";

    int totalThreats = 0;
    int infectedFiles = 0;

    // Write each file's results
    for (const ScanResult &r : results)
    {
        totalThreats += r.threatsFound;
        if (r.isInfected)
            infectedFiles++;

        string status = r.isInfected ? "[INFECTED]" : "[CLEAN]   ";
        outFile << status << " " << r.filename
                << " (" << r.threatsFound << " threats)\n";
    }

    // Write summary
    outFile << "----------------------------------------\n";
    outFile << "Total Threats Detected: " << totalThreats << "\n";
    outFile << "Infected Files: " << infectedFiles << "\n";
    outFile << "Clean Files: " << (results.size() - infectedFiles) << "\n";
    outFile << "========================================\n";

    outFile.close();
    cout << "[Report] Report exported successfully!" << endl;
}