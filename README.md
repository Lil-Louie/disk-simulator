DiskSim — Disk Scheduling Simulator in C++

A modular, event-driven disk scheduling simulator implementing and comparing five classic disk I/O scheduling algorithms:

FCFS — First-Come, First-Served
ST — Same Track Clustering
Pick-Up — Greedy track-based optimization
LOOK — Optimized SCAN (skips empty tracks)
C-LOOK — Circular LOOK, fairer version of LOOK
Features

Event-driven simulation using custom TimerEvent and DiskDoneEvent classes
Real-time queue tracking and performance statistics:
Min/Max/Average queue lengths
Total requests completed
Clean OOP design using C++17
Easy to extend and test with custom input files
Build Instructions

Requirements
C++17 compatible compiler (g++, clang++)
Make (or compile manually)
Build and Run
# Compile using Makefile
make alldisks.x

# Run simulation with input file
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
📂 Project Structure

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
💡 Notes

Input file format: arrival_time track sector
Designed for learning purposes and academic simulation of disk scheduling algorithms
