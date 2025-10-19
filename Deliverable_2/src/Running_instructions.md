# SentinelAV - Quick Start

## Git Bash

```bash
cd SentinelAV-DSA-Based-Antivirus/Deliverable_2/src
g++ -std=c++11 main.cpp signatureDB.cpp scanner.cpp report.cpp -o sentinelAV
./sentinelAV
```

## PowerShell

```powershell
cd C:\Users\reyan\OneDrive\Desktop\DSA\project\SentinelAV-DSA-Based-Antivirus\Deliverable_2\src
g++ -std=c++11 main.cpp signatureDB.cpp scanner.cpp report.cpp -o sentinelAV
.\sentinelAV
```

(Replace `reyan` with your username)

---

## One-Line Commands

**Git Bash:**
```bash
cd Deliverable_2/src && g++ -std=c++11 main.cpp signatureDB.cpp scanner.cpp report.cpp -o sentinelAV && ./sentinelAV
```

**PowerShell:**
```powershell
cd Deliverable_2\src; g++ -std=c++11 main.cpp signatureDB.cpp scanner.cpp report.cpp -o sentinelAV; .\sentinelAV
```

---

## Troubleshooting

**"g++ not found"** → Install MinGW

**"Could not open file"** → Make sure you're in `Deliverable_2/src/` folder

**"multiple definition of main"** → Delete main() function from report.cpp, recompile