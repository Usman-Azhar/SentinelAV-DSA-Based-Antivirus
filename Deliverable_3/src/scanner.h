#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "signatureDB.h"
#include "queue.h"

using namespace std;

struct DetectionResult
{
    string line;
    string matchedSignature;
    int lineNumber;

    DetectionResult(string l = "", string sig = "", int num = 0)
        : line(l), matchedSignature(sig), lineNumber(num) {}
};

class Scanner
{
private:
    int filesScanned;
    Queue<DetectionResult> detectionQueue;
    int currentFileThreats;

public:
    Scanner();

    void scanFile(const string &filename, const SignatureDB &sigDB);
    int getLastFileThreatCount() const;
    Queue<DetectionResult> &getDetections();

    ~Scanner();
};

#endif