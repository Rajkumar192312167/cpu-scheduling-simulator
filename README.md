# CPU Scheduling Algorithm Simulator (C)

## Overview
This project implements a CPU Scheduling Simulator in C to demonstrate how different scheduling algorithms allocate CPU time to processes.

The simulator considers arrival time, burst time, and time quantum (for Round Robin) and computes key performance metrics such as waiting time and turnaround time.

## Algorithms Implemented
- First Come First Serve (FCFS)
- Shortest Job First (Non-preemptive)
- Round Robin (Preemptive)

## Features
- Handles process arrival times and CPU idle periods
- Supports preemptive and non-preemptive scheduling
- Calculates waiting time and turnaround time for each process
- Compares efficiency and fairness of scheduling algorithms

## Input
- Number of processes
- Arrival time and burst time for each process
- Time quantum (for Round Robin)

## Output
- Execution order of processes
- Waiting time and turnaround time
- Average waiting time and turnaround time for each algorithm

## Learning Outcomes
- Understanding of CPU scheduling strategies
- Difference between preemptive and non-preemptive algorithms
- Impact of scheduling on waiting time and fairness
- Practical experience with time-based simulation in C

## Tools Used
- C Programming Language
- GCC Compiler
- VS Code
