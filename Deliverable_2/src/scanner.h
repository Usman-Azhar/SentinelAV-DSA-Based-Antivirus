#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include "signatureDB.h"
#include "queue.h"

using namespace std;

struct DetectionResult{
    string line;                // line of text where virus was found
    string matchedSignature;    // virus signature that matched
    int lineNumber;             // line number
};

class Scanner
{
private:
    int filesScanned;                       // Track of number of files scanned
    Queue<DetectionResult> DetectionQueue;  // Queue from queue.h to store detectionresults Objects

    bool findPatternInLine(const string& line, const string& patter, int lineNum){}; // checks if pattern was matched or not
public:
    Scanner();

    void ScanFile(string const& filename, const SignatureDB& SignDb){};     // Read files and Scans for viruses

    int GettreatCount(){};                                                  // returns Total treats found

    Queue<DetectionResult>& getDetections();                                // queue for all detections

    ~Scanner();
};


#endif