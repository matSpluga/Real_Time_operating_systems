# Real-Time Scheduling Exercises

This folder contains C++ implementations and variants of real-time scheduling exercises based on POSIX threads. The main focus is **Rate Monotonic Scheduling (RMS)**, periodic task execution, deadline monitoring, and the handling of aperiodic work and shared resources.

## Requirements

- Linux
- `g++`
- POSIX Threads
- A system that supports the `SCHED_FIFO` real-time scheduling policy

Compile a selected source file from this directory with optimization disabled:

```bash
g++ -O0 RM.cpp -o rm -pthread
./rm
```

Replace `RM.cpp` with the source file you want to test. Some variants request real-time scheduling priorities; on a typical Linux system this may require elevated privileges or suitable real-time limits. For example:

```bash
sudo ./rm
```

Use real-time priorities carefully: a process using `SCHED_FIFO` incorrectly can monopolize CPU time. The programs also include timing measurements, so results depend on the machine, kernel, and system load.

## Source files

| File | Main topic |
|---|---|
| `RM-start.cpp` | Starter template for the periodic RMS exercise. It provides the scheduling data structures and setup, leaving parts of the task implementation to be completed. |
| `RM.cpp` | Baseline RMS implementation with three periodic tasks, periodic activation, execution-time measurements, and deadline-miss monitoring. |
| `RM-mut.cpp` | RMS with shared-memory access and mutex-protected critical sections; intended for investigating synchronization and resource access. |
| `RM-prc.cpp` | RMS with priority-ceiling protocol support for mutexes, to study priority inversion and resource-sharing control. |
| `RM-APS.cpp` | RMS extended with a Polling Server to service aperiodic requests alongside periodic tasks. |
| `RM-ABG.cpp` | RMS extended with aperiodic tasks and synchronization mechanisms, for comparing approaches to aperiodic workload handling. |

The `.jpg` files are visual outputs associated with the corresponding scheduling variants (`RM.jpg`, `RM-mut.jpg`, `RM-prc.jpg`, `RM-APS.jpg`, and `RM-ABG.jpg`).

## Concepts to investigate

- RMS priority assignment: tasks with shorter periods receive higher priorities.
- CPU utilization and schedulability analysis, using the execution-time estimates and task periods.
- Periodic releases and absolute-time sleeps.
- Worst-case execution-time (WCET) measurement and deadline-miss counting.
- Mutual exclusion and priority inversion when tasks share resources.
- Priority-ceiling synchronization.
- Aperiodic task servicing through a Polling Server or other synchronization strategies.

## Experimental notes

The source comments recommend compiling with `-O0` to make execution-time behaviour more repeatable. CPU frequency scaling, turbo boost, background load, and kernel scheduling behaviour can still affect measurements. Any frequency-governor or turbo settings mentioned in source comments are optional experimental controls, not prerequisites for compiling the programs.
