#include "scanner.h"
#include <iostream>
#include <fstream>

using namespace std;

Scanner::Scanner() : filesScanned(0), currentFileThreats(0)
{
    cout << "[Scanner] File scanner initialized" << endl;
}

// Main scanning logic: Read file and check each line against all signatures
// Algorithm: Naive string matching O(n * m * k) where:
// n = lines in file, m = signatures, k = average line length
void Scanner::scanFile(const string &filename, const SignatureDB &sigDB)
{
    cout << "\n[Scanner] Scanning: " << filename << endl;

    // Open file for reading
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "[Scanner] ERROR: Unable to open file!" << endl;
        currentFileThreats = 0;
        return;
    }

    string line;
    int lineNumber = 1;
    int sigCount = sigDB.getSignatureCount();
    currentFileThreats = 0; // Reset counter for this file

    // Process file line by line
    while (getline(file, line))
    {
        // Check current line against ALL signatures
        for (int i = 0; i < sigCount; i++)
        {
            string signature = sigDB.getSignatureAt(i);

            // Check if signature exists in this line
            // string.find() returns position or npos (not found)
            if (line.find(signature) != string::npos)
            {
                // Threat detected! Create result and add to queue
                DetectionResult result(line, signature, lineNumber);
                detectionQueue.enqueue(result); // FIFO queue stores in order
                currentFileThreats++;

                // Report detection immediately
                cout << "  [THREAT] Line " << lineNumber
                     << ": Detected '" << signature << "'" << endl;
            }
        }
        lineNumber++;
    }

    file.close();
    filesScanned++;

    // Summary for this file
    if (currentFileThreats == 0)
    {
        cout << "  [CLEAN] No threats detected" << endl;
    }
    else
    {
        cout << "  [INFECTED] Total threats found: " << currentFileThreats << endl;
    }
}

// Return threat count from most recently scanned file
int Scanner::getLastFileThreatCount() const
{
    return currentFileThreats;
}

// Provide access to the detection queue
// Allows report generation to process all detections
Queue<DetectionResult> &Scanner::getDetections()
{
    return detectionQueue;
}

// Cleanup and final statistics
Scanner::~Scanner()
{
    cout << "[Scanner] Scan complete. Total files scanned: " << filesScanned << endl;
}