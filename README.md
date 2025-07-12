# DiskSim — Disk Scheduling Simulator in C++

A modular, event-driven disk scheduling simulator written in C++. It implements and compares five classic disk I/O scheduling algorithms:

- **FCFS** — First-Come, First-Served  
- **ST** — Same Track Clustering  
- **Pick-Up** — Greedy track-based optimization  
- **LOOK** — Optimized SCAN (skips empty tracks)  
- **C-LOOK** — Circular LOOK, a fairer version of LOOK  

---

## Features

- Event-driven architecture using custom `TimerEvent` and `DiskDoneEvent` classes  
- Real-time queue tracking and statistics:
  - Total requests completed  
  - Minimum, maximum, and average queue lengths  
- Clean object-oriented design using modern C++ (C++17)  
- Modular and extensible structure for testing new algorithms  

---

## Build Instructions

### Requirements

- A C++17-compatible compiler (`g++`, `clang++`, etc.)  
- `make` (optional but recommended)  

### Build and Run

To compile the simulator:

```bash
make alldisks.x

# Compile using Makefile
make alldisks.x

To run the simulation using an input request file:
./alldisks.x inputRequests.txt

Sample Output

========== FINAL DISK STATS ==========

[FCFS] Stats:
  Total Requests Completed: 10
  Min Queue Length: 0
  Max Queue Length: 3
  Avg Queue Length: 2.20

[ST] Stats:
  Total Requests Completed: 10
  Min Queue Length: 0
  Max Queue Length: 3
  Avg Queue Length: 1.20

...
Project Structure

DiskSim/
├── CommonFiles/         # Shared data types and request logic
├── EventQueue/          # Event-driven simulation core
├── FCFS_Queue/          # First-Come, First-Served implementation
├── ST_Queue/            # Same Track clustering implementation
├── PU_Queue/            # Pick-Up algorithm
├── Look_Queue/          # LOOK scheduling
├── CLook_Queue/         # C-LOOK scheduling
├── inputRequests.txt    # Sample input
├── main.cpp             # Entry point
├── Makefile
 Notes

Input file format: arrival_time track sector
Designed for learning purposes and academic simulation of disk scheduling algorithms
