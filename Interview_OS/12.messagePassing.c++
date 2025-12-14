/*
“Message Passing Gone Wrong”

Consider the following C++ code:

#include <atomic>

std::atomic<bool> ready{false};
int data = 0;

void producer() {
    data = 42;                             // (A)
    ready.store(true, std::memory_order_relaxed); // (B)
}

void consumer() {
    while (!ready.load(std::memory_order_relaxed)) {
        // spin
    }
    int x = data;                          // (C)
    use(x);
}

Part A

Is it guaranteed that x == 42 in consumer()?

Explain why or why not using the C++ memory model.
[Ans]
No. 
std::memory_order_relaxed not guarantees ordering the sequence of instructions.
Theoritically, 
x == 0 is possible, for (B) -> (C) -> (A) sequence of instructions.

⸻

Part B

List all possible outcomes allowed by the C++ memory model.
[Ans]

x = 0; (B) -> (C) -> (A)
x = 42; for other sequences
⸻

Part C

Fix the code using the minimum memory ordering changes
(no mutexes, no condition variables).

ready.store(true, std::memory_order_release); // (B)
 while (!ready.load(std::memory_order_acquire)) {
⸻

Part D (Follow-ups interviewers love)
	1.	Why does memory_order_relaxed fail here?
[ans]: Since it allows reordering the sequence of instructuion.
	2.	Why is volatile not a fix?
[ans]: Volatile is only avoid register level optimizations. Reordering by processor/compiler doesn't help even volatile is used.
	3.	How does this behave differently on x86 vs ARM?
[ans]: Cache lines could be different for RISC(x86) vs CISC(ARM). CPU level optimizations could be different. Issues could be theoritically common.
	4.	What changes if data is also atomic?
[ans]: It just gurantees atomicity of (A) and (C). Still reordering issues present.
	5.	Can reordering happen even if the compiler does nothing “wrong”?
[ans]: Yes, reordering is based on Compiler or CPU level optimizations.

⸻
*/