<div align="center">

# CPU Job Scheduler — IIT G2406 T1

**C++ simulator implementing 4 CPU scheduling algorithms (FCFS, SJF, Priority, Round Robin) with O(1) core operations, algorithm benchmarking across process sets, and Gantt chart visualization of turnaround and wait times.**

[![C++](https://img.shields.io/badge/C++-17-00599C?style=flat&logo=cplusplus&logoColor=white)](https://isocpp.org)
[![Domain](https://img.shields.io/badge/Domain-Operating%20Systems-6A5ACD?style=flat)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=flat)](LICENSE)

</div>

---

## The Problem

CPU scheduling determines which process runs next — directly impacting system throughput, response time, and fairness. Different algorithms make different trade-offs: FCFS is simple but can starve short jobs; SJF minimizes wait time but requires burst time knowledge; Round Robin ensures fairness via time slicing. This simulator implements all four, measures their performance on identical process sets, and visualizes results via Gantt charts.

---

## Algorithms Implemented

| Algorithm | Strategy | Best for |
|-----------|----------|---------|
| **FCFS** — First Come First Served | Processes run in arrival order | Simple batch systems, no preemption |
| **SJF** — Shortest Job First | Shortest burst time runs next | Minimizing average wait time |
| **Priority** | Highest priority process runs next | Real-time or tiered workloads |
| **Round Robin (RR)** | Each process gets a fixed time quantum | Fair CPU sharing, interactive systems |

---

## Technical Design

| Property | Detail |
|----------|--------|
| Core operations | **O(1)** constant-time for scheduling decisions |
| Process model | Each process: PID · arrival time · burst time · priority |
| Metrics computed | Turnaround time · wait time · completion time · CPU utilization |
| Visualization | Gantt chart output printed per algorithm for full process timeline |
| Benchmarking | All 4 algorithms run on the same process set — direct metric comparison |

---

## Results

| Metric | Value |
|--------|-------|
| Scheduling algorithms | **4** (FCFS · SJF · Priority · Round Robin) |
| Core operation complexity | **O(1)** |
| Output | Gantt chart per algorithm + turnaround/wait time table |
| Benchmarking | All algorithms compared on identical process inputs |

---

## Demo

### Video Walkthrough
> *2-minute walkthrough: process input → run all 4 schedulers → compare Gantt charts → interpret wait and turnaround times.*

[![Watch the Demo](https://img.shields.io/badge/Watch%20Demo-Coming%20Soon-red?style=for-the-badge&logo=youtube)](#)

### Sample Output
Algorithm: Round Robin (Quantum = 3)

Gantt Chart:
| P1 | P2 | P3 | P1 | P2 | P4 | P3 |
0 3 6 9 12 15 18 21

Process Arrival Burst Completion Turnaround Wait
P1 0 6 12 12 6
P2 1 4 15 14 10
P3 2 6 21 19 13
P4 3 3 18 15 12

Output of the similarity index check
![image](https://github.com/user-attachments/assets/078b30cd-3801-4610-9eb1-0dbbbbb6336e)

---
## Tech Stack
| Layer | Tool |
|-------|------|
| Language | C++ (17) |
| Concepts | OS process scheduling · queue data structures · time-slice management |
| Output | Console Gantt charts + performance metric tables |
---

## Setup & Run
**Prerequisites:** C++ compiler (g++ / clang++)
```bash
# Compile
g++ -std=c++17 src/*.cpp -o scheduler
# Run
./scheduler
Enter process details (PID, arrival time, burst time, priority) when prompted
The program outputs Gantt charts and metric tables for all 4 algorithms
