#include "scanner.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor - initializes scanner with 0 files scanned
Scanner::Scanner() : filesScanned(0) {
    cout << "[Scanner] Scanner initialized (using Queue for detections)" << endl;
}

// Main scanning function - reads file and searches for virus patterns
void Scanner::scanFile(const string& filename, const SignatureDB& sigDB) {
    cout << "\n[Scanner] Scanning file: " << filename << endl;
    
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "[Scanner] ERROR: Could not open file!" << endl;
        return;
    }
    
    string line;
    int lineNumber = 1;
    
    // Read file line by line
    while (getline(file, line)) {
        // For each line, check ALL signatures in the database
        // D2: Simple approach - check each signature one by one
        // D3 TODO: Will use Aho-Corasick for efficient multi-pattern matching
        
        int sigCount = sigDB.getSignatureCount();
        for (int i = 0; i < sigCount; i++) {
            string signature = sigDB.getSignatureAt(i);
            findPatternInLine(line, signature, lineNumber);
        }
        
        lineNumber++;
    }
    
    file.close();
    filesScanned++;
    
    cout << "[Scanner] Scan complete. Threats found: " << getThreatCount() << endl;
}

// Helper function to find pattern in a line
bool Scanner::findPatternInLine(const string& line, const string& pattern, int lineNum) {
    // Simple string search - check if pattern exists in line
    if (line.find(pattern) != string::npos) {
        // Pattern found! Create detection result
        DetectionResult result;
        result.line = line;
        result.matchedSignature = pattern;
        result.lineNumber = lineNum;
        
        // Add to detection queue
        detectionQueue.enqueue(result);
        cout << "  [!] Threat at line " << lineNum << ": Found '" << pattern << "'" << endl;
        
        return true;  // Pattern was found
    }
    return false;  // Pattern not found
}

// Get total number of threats detected
int Scanner::getThreatCount() {
    return detectionQueue.getSize();
}

// Get reference to the detection queue
queue<DetectionResult>& Scanner::getDetections() {
    return detectionQueue;
}

// Display implementation status
void Scanner::displayImplementationStatus() const {
    cout << "\n[Scanner] Implementation Status:" << endl;
    cout << "  D2: Queue for detections - IMPLEMENTED" << endl;
    cout << "  D2: File scanning - IMPLEMENTED" << endl;
    cout << "  D2: Simple pattern matching - IMPLEMENTED" << endl;
    cout << "  D3: Aho-Corasick pattern matching - DECLARED (TODO)" << endl;
    cout << "  D3: Parallel scanning - DECLARED (TODO)" << endl;
}

// Destructor
Scanner::~Scanner() {
    // Queue destructor will handle cleanup
    cout << "[Scanner] Scanner closed. Total files scanned: " << filesScanned << endl;
}