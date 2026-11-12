# POSIX Threads Exercises

This folder contains three introductory exercises on multithreading in C/C++ using the POSIX Threads (`pthread`) library. For each exercise, both a completed example and a `_start` skeleton are provided, in Italian and English.

## Requirements

- Linux or another POSIX-compatible environment
- `g++` (or `gcc`)
- POSIX Threads development support

Compile the examples from this directory with `-pthread`:

```bash
g++ threadex1eng.cpp -o thread1 -pthread
./thread1

g++ threadex2eng.cpp -o thread2 -pthread
./thread2

g++ threadex3eng.cpp -o thread3 -pthread
./thread3
```

The Italian versions are `threadex1ita.cpp`, `threadex2ita.cpp`, and `threadex3ita.cpp`. The corresponding starter files end in `_start.cpp`.

## Exercise 1 — Thread creation and termination

**Files:** `threadex1eng.cpp`, `threadex1ita.cpp`

Creates two independent threads with `pthread_create()`. Each thread executes the same routine and prints its own message repeatedly. The main thread waits for both threads with `pthread_join()` and retrieves their return values, which are provided through `pthread_exit()`.

Topics: thread creation, argument passing, joining threads, and returning a value from a thread.

## Exercise 2 — Race conditions and mutexes

**Files:** `threadex2eng.cpp`, `threadex2ita.cpp`

Two threads concurrently increment a shared counter. The update is deliberately split into multiple operations, with a delay between reading and writing the shared value, to make race conditions easier to observe. A `pthread_mutex_t` protects the critical section.

Try running the program with the mutex lock/unlock calls enabled and disabled, and compare the results. Without mutual exclusion, concurrent updates can be lost.

Topics: shared data, critical sections, race conditions, and mutex synchronization.

## Exercise 3 — Condition variables

**Files:** `threadex3eng.cpp`, `threadex3ita.cpp`

Two threads coordinate access to a shared counter. One thread waits on a condition variable until the other thread signals that it can proceed. A mutex protects the shared state, while `pthread_cond_wait()` and `pthread_cond_signal()` provide the notification mechanism.

Topics: condition variables, signaling, waiting with a mutex, and synchronization between threads.

## Notes

- Thread output may be interleaved; the order of printed messages is not deterministic.
- The second exercise intentionally includes a one-second delay and can therefore take a while to complete.
- The `_start.cpp` files are incomplete templates intended to be filled in as part of the exercises.
