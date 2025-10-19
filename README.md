# SentinelAV

A C++ antivirus prototype that demonstrates practical application of data structures and algorithms for file threat detection.

## About the Project

SentinelAV is designed to scan files and identify potential threats by matching against a database of known virus signatures. The project focuses on implementing efficient data structures to handle signature storage, pattern searching, and result organization.

The system reads virus signatures from a database, scans input files line-by-line searching for matches, and generates a ranked report of threats found.

**Team:** Usman Azhar, Reyan Kashif, Malik Abdullah

---

## How It Works

1. **Load Signatures** - Reads known virus patterns from a signature database
2. **Scan Files** - Reads target file and searches for matching patterns
3. **Store Detections** - Queues any matches found during scanning
4. **Generate Report** - Ranks and displays threats by severity

---

## Project Structure

```
SentinelAV/
├── src/                    # Source code
│   ├── queue.h            # Generic queue implementation
│   ├── linkedList.h       # Generic linked list implementation
│   ├── signatureDB.h/cpp  # Virus signature storage
│   ├── scanner.h/cpp      # File scanning engine
│   ├── report.h/cpp       # Results ranking and display
│   └── main.cpp           # Program entry point
├── data/                   # Test data
│   ├── virus_signatures.txt   # Sample virus patterns
│   └── sample_input.txt       # Test file to scan
└── docs/                   # Documentation
    ├── D2_Report.docx     # Detailed implementation report
    └── D2_Slides.pptx     # Presentation slides
```

---

## Core Components

**SignatureDB** - Manages the virus signature database
- Loads patterns from file
- Provides search functionality for pattern lookup
- Uses linked list for efficient storage

**Scanner** - Performs the actual file scanning
- Reads files line by line
- Searches for virus signatures in content
- Stores detection results in a queue

**Report** - Analyzes and displays results
- Collects all detections from scanning
- Sorts results by threat severity
- Generates formatted summary output

**Queue & LinkedList** - Generic data structures
- Queue: FIFO storage for detection results
- LinkedList: Dynamic storage for signatures

---

## Compilation

**Requirements:**
- C++11 compiler (g++)

**Compile:**
```bash
g++ -std=c++11 src/main.cpp src/signatureDB.cpp src/scanner.cpp src/report.cpp -o sentinelAV
```

---

## Running the Program

```bash
./sentinelAV
```

**Expected Output:**
- Loads virus signatures from database
- Scans test file for threats
- Displays ranked list of detected threats
- Shows scan statistics and summary

---

## Key Features

- **Efficient Storage** - Uses linked lists for dynamic signature management
- **FIFO Ordering** - Queue maintains detection order as found
- **Result Ranking** - Threats sorted by severity
- **Error Handling** - Validates file access and data integrity
- **Modular Design** - Separate components for easy maintenance and extension

---

## Technical Details

**Data Structures:**
- Linked lists for signature storage and traversal
- Queues for ordered result collection
- Dynamic arrays for result ranking

**Algorithms:**
- Linear search for pattern matching
- Recursive searching through signature database
- Sorting for result organization

**Time Complexity:**
- Signature search: O(n) where n = number of signatures
- File scanning: O(n*m) where n = file size, m = pattern size
- Result sorting: O(k²) where k = number of detections

---

## Future Enhancements

The current implementation uses fundamental data structures and algorithms. Future versions could incorporate:

- Advanced tree structures for faster pattern matching
- Hash tables for instant signature lookups
- Optimized sorting algorithms for better performance
- Pre-screening filters to skip clean files
- Multi-file batch scanning
- Real-time signature database updates

---

## Testing

All components have been verified for:
- Successful compilation without errors
- Correct program execution
- Proper file I/O handling
- Accurate threat detection and reporting
- Memory management and cleanup

---

## Getting Started

**Clone the repository:**
```bash
git clone <repository-url>
cd SentinelAV
```

**Compile and run:**
```bash
g++ -std=c++11 src/main.cpp src/signatureDB.cpp src/scanner.cpp src/report.cpp -o sentinelAV
./sentinelAV
```

---

## Documentation

- **D2_Report.docx** - Complete implementation details, testing results, and data structure explanations
- **D2_Slides.pptx** - Presentation slides covering architecture and demonstration

---

**Status:** Deliverable 2 Complete