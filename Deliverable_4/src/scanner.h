#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "signatureDB.h"
#include "queue.h"

using namespace std;

// DetectionResult: Stores information about a single virus detection
// Used to record where and what was found during file scanning
struct DetectionResult
{
    string line;             // The actual line of text containing the virus
    string matchedSignature; // Which virus pattern was matched
    int lineNumber;          // Line number in the file (for reporting)

    DetectionResult(string l = "", string sig = "", int num = 0)
        : line(l), matchedSignature(sig), lineNumber(num) {}
};

// Scanner: File scanning engine that detects viruses in text files
// Process: Read file → Check each line → Compare with signatures → Queue results
class Scanner
{
private:
    int filesScanned;                      // Total files processed
    Queue<DetectionResult> detectionQueue; // FIFO queue of all detections found
    int currentFileThreats;                // Threat count for the current file being scanned

public:
    Scanner();

    // Main scanning function
    // Process: Open file → Read line by line → Search for each signature → Record matches
    void scanFile(const string &filename, const SignatureDB &sigDB);

    int getLastFileThreatCount() const;      // Get threat count from last scanned file
    Queue<DetectionResult> &getDetections(); // Access the detection queue

    void displayImplementationStatus() const;

    ~Scanner();
};

#endif