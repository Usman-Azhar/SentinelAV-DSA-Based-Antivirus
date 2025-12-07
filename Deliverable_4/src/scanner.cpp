#include "scanner.h"
#include <iostream>
#include <fstream>

using namespace std;

Scanner::Scanner() : filesScanned(0), currentFileThreats(0)
{
    cout << "[Scanner] File scanner initialized" << endl;
}

void Scanner::scanFile(const string &filename, const SignatureDB &sigDB)
{
    cout << "\n[Scanner] Scanning: " << filename << endl;

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
    currentFileThreats = 0;

    while (getline(file, line))
    {
        for (int i = 0; i < sigCount; i++)
        {
            string signature = sigDB.getSignatureAt(i);

            if (line.find(signature) != string::npos)
            {
                DetectionResult result(line, signature, lineNumber);
                detectionQueue.enqueue(result);
                currentFileThreats++;

                cout << "  [THREAT] Line " << lineNumber
                     << ": Detected '" << signature << "'" << endl;
            }
        }
        lineNumber++;
    }

    file.close();
    filesScanned++;

    if (currentFileThreats == 0)
    {
        cout << "  [CLEAN] No threats detected" << endl;
    }
    else
    {
        cout << "  [INFECTED] Total threats found: " << currentFileThreats << endl;
    }
}

int Scanner::getLastFileThreatCount() const
{
    return currentFileThreats;
}

Queue<DetectionResult> &Scanner::getDetections()
{
    return detectionQueue;
}

Scanner::~Scanner()
{
    cout << "[Scanner] Scan complete. Total files scanned: " << filesScanned << endl;
}