---
geometry:
- top=25mm
- left=20mm
- right=20mm
- bottom=30mm
documentclass: extarticle
fontsize: 12pt
numbersections: true
title: Lecture 2 (Synchronisation)
--- 

# Definition
1. Do operation at a certain time $T$
1. Two or a set of events should happen together - barrier
1. Any two events should not happen together - mutual exclusion, critical section
1. Event A should happen after event B - conditions

# Logical Clock
1. Every entity maintains a counter
1. Increment happens at every 'event' of that entity
1. Interaction between entities happens via `data + counter`
1. On receiving message, if recipient counter < received counter, then increase local counter to received counter and increment it by one since receiving is also an event
1. This is **Lamport's Timestamp Algorithm**
1. It allows partial ordering of events
1. Causality is maintained: $A \to B \implies time(A) < time(B)$, however the inverse need not be true, all we know is $time(A) < time(B) \implies B \not\to A$
1. We can have a vector clock instead to have strong causality (so that the inverse is also true)
1. Partial ordering can be changed to total ordering using process ID, but isn't much useful

# Lower Level Primitives for Synchronisation
1. Locks
1. Semaphores
1. Register
1. Transactional memory

# Progress
1. Starvation - each synchroniser gets to make progress, it is starvation-free
1. Deadlock - if each synchroniser gets to make some progress, it is deadlock-free

## Types of Primitives
- Busy-wait vs OS-scheduled
    1. Busy-wait - `while (!condition);`
    1. OS-scheduled - scheduler sends signal to start computation, until then process is inactive
- Blocking vs non-blocking
- Fairness vs liveness

## Fairness
1. Strong - if any synchroniser is ready infinitely often, then it should be executed infinitely often
1. Weak - if any synchroniser is ready, it should be executed eventually


|     | Not lock-based (independent of scheduler)    | Lock-based (OS scheduling)    |
|---------------- | --------------- | --------------- |
| Everyone progresses    | Wait free    | Starvation free    |
| Someone progresses    | Lock free    | Deadlock free    |

# Lock
1. `mutex` and `lock_guard` is used
1. `mutex.lock()` can also be used
1. Alternatively `unique_lock` can be used which provides more freedom

## Types
1. Re-entrant
1. Recursive
1. Timed
1. Exclusive
1. Shared

# Condition Variable
```c++
// defining
std::condition_variable acv;

// implement wait
acv.wait(some_lock);

// notify to release the wait
acv.notify_one();
// or
acv.notify_all();
```

# Barrier
Wait for all
```c++
// works only in C++ 2020
// define
std::barrier abarrier(count, completion_function);

// on reaching the barrier
abarrier.arrive_and_wait(); // barrier waits here until 'count' number of synchronisers
                            // have reached
                            // and then calls completion_function
```

# Critical Section
```c++
// omp automatically locks code with same names
#pragma omp critical (aname)
{
    // mutually excluded code
}
```
