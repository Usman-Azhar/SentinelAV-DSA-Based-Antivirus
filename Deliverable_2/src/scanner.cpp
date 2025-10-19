#include "scanner.h"
#include <iostream>
#include <fstream>

using namespace std;

Scanner:: Scanner() : filesScanned(0){

}

void Scanner :: ScanFile(string const& filename, const SignatureDB& SignDb){
    cout <<"Scanning File: "<<filename<<endl;

    ifstream file(filename);

    if(!file.is_open()){
        cout<<"File Could not be Opened."<<endl;
        return;
    }

    string line;
    int linenumber=1;

    while (getline(file, line)) {
        // TODO in D3: actual pattern searching here
        lineNumber++;
    }

    filesScanned++;

    cout<<"File Scanned Successfully, DETECTION="<< GettreatCount;
};

bool Scanner:: findPatterInLine(const string& line, const string& matchedSignature, int lineNumber){
    if (line.find(patter)!=string::npos){   // Search pattern in line , If found npos means -> not found
        DetectionResult result;             // Create a detection result
        result.line = line;                 // Store the line
        result.matchedSignature=pattern;    // Store the virus pattern
        result.lineNumber=linenum;          // Store the line number
        
        detectionQueue.enqueue(result);     // Add to queue
        cout << "  Threat Line " << lineNum << ": Found '" << pattern << "'" << endl;

        return true;                        // Pattern was found
    }
    return false;                           // Pattern was not found
}

int Scanner :: getThreatCount(){
    return detectionQueue.getSize();        // Return size of the queue
}

Queue<DetectionResult> &Scanner ::getDetections(){
    return DetectionQueue;                  // Return reference to the detection queue
}

