# SentinelAV: DSA-Based Antivirus Engine

[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue)](https://cplusplus.com/)

## 👥 Team Members

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/Usman-Azhar">
        <img src="https://avatars.githubusercontent.com/u/190142643?v=4" width="100px;" alt="Usman Azhar"/><br/>
        <b>Usman Azhar</b>
      </a><br/>
      <sub>Project Lead & Lead Developer</sub><br/>
      <a href="https://github.com/Usman-Azhar">@Usman-Azhar</a>
    </td>
    <td align="center">
      <a href="https://github.com/Reyan-kashif">
        <img src="https://avatars.githubusercontent.com/u/207247821?v=4" width="100px;" alt="Reyan Kashif"/><br/>
        <b>Reyan Kashif</b>
      </a><br/>
      <sub>Algorithm Specialist</sub><br/>
      <a href="https://github.com/Reyan-kashif">@Reyan-kashif</a>
    </td>
    <td align="center">
      <a href="https://github.com/abdullahmalik2k5-cyber">
        <img src="https://avatars.githubusercontent.com/u/236664026?v=4" width="100px;" alt="Malik Abdullah"/><br/>
        <b>Malik Abdullah</b>
      </a><br/>
      <sub>Core Developer & Data Structure Specialist</sub><br/>
      <a href="https://github.com/abdullahmalik2k5-cyber">@Abdullah-Malik</a>
    </td>
  </tr>
</table>

---

A robust antivirus engine prototype that leverages practical applications of **Data Structures and Algorithms (DSA)** for real-time threat detection and file scanning. Built entirely in C++, SentinelAV exemplifies the fusion of theoretical computer science concepts and cybersecurity practices.

---

## 📋 Project Overview

SentinelAV serves as a learning-driven exploration of how real-world antivirus engines operate, emphasizing modular design, efficient data handling, and scalable architecture. It features a comprehensive virus signature database, efficient file scanning mechanisms, and thorough threat ranking and reporting.

### Core Objectives:
- Showcase DSA applications in cybersecurity.
- Develop a functional antivirus prototype.
- Optimize threat detection efficiency.

---

## 🌟 Key Features

| Feature              | Highlights                                               |
|----------------------|----------------------------------------------------------|
| **Dynamic Storage**  | Linked lists for adaptive virus signature management.    |
| **Order Preservation** | Queue-based discovery to prioritize relevant threats.  |
| **Severity Ranking** | Organized threat display based on criticality.           |
| **Scalable Design**  | Modular components ensuring code reusability.            |
| **Robust Validation** | Secure file I/O and edge-case handling.                 |
| **Custom Templates** | Reusable data structure implementations for scalability. |

---

## 🔧 Core Components

1. **SignatureDB**: Manages virus definitions using linked lists for optimal memory utilization.
2. **Scanner**: Efficiently reads input files and matches against virus signatures.
3. **Report Generator**: Sorts and formats detection results by severity for clear insights.
4. **Queue Template**: Ensures FIFO storage for threat results.
5. **LinkedList Template**: Allows dynamic handling of virus signatures.

---

## ⚙️ How It Works

```
1. Load Signatures  → 2. Scan Files  → 3. Store Detections  → 4. Generate Reports
```
- Load virus patterns from the signature database.
- Scan input files line-by-line and store matches in a queue.
- Rank stored detections by severity and generate formatted reports.

---

## 🚀 Getting Started

### Prerequisites:
- C++11-compatible compiler (g++, clang).
- Command-line access.

### Installation & Execution:
1. **Clone the repository**:
   ```bash
   git clone https://github.com/Usman-Azhar/SentinelAV-DSA-Based-Antivirus.git
   cd SentinelAV-DSA-Based-Antivirus
   ```
2. **Navigate to the source directory**:
   ```bash
   cd Deliverable_4/src
   ```
3. **Compile and run the antivirus**:
   ```bash
   g++ -std=c++11 main.cpp signatureDB.cpp scanner.cpp report.cpp -o sentinelAV
   ./sentinelAV
   ```

---

## 📚 Learning Outcomes

- Practical insights into DSA applications like linked lists and queues.
- Understanding pattern-matching algorithms in file scanning.
- Building scalable applications with modular design and template classes.

---

## 📈 Performance Metrics

- **Best-case scanning speed**: O(n)
- **Dynamic detection storage**: O(k) space complexity for queue usage.

---

For project details, visit the [repository](https://github.com/Usman-Azhar/SentinelAV-DSA-Based-Antivirus). Contribute, explore, and learn—a project dedicated to making cybersecurity education accessible and impactful.
