
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "signatureDB.h"
#include "queue.h"

using namespace std;

// Structure to hold information about a detected threat
struct DetectionResult {
    string line;                // Line of text where virus was found
    string matchedSignature;    // Virus signature that matched
    int lineNumber;             // Line number in the file
};

class Scanner {
private:
    int filesScanned;                           // Track number of files scanned
    Queue<DetectionResult> detectionQueue;      // Queue to store all detections
    
    // Helper function - checks if pattern exists in a line
    bool findPatternInLine(const string& line, const string& pattern, int lineNum);
    
public:
    // Constructor
    Scanner();
    
    // Main scanning function - reads file and scans for viruses
    void scanFile(const string& filename, const SignatureDB& sigDB);
    
    // Get total number of threats found
    int getThreatCount() const;
    
    // Get reference to the detection queue
    Queue<DetectionResult>& getDetections();
    
    // Display implementation status (for D2 demo)
    void displayImplementationStatus() const;
    
    // Destructor
    ~Scanner();
};

#endif