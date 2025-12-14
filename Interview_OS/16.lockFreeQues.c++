/*
Question

You are implementing a lock-free stack using CAS (compare-and-swap) on a shared pointer:

struct Node {
    int val;
    Node* next;
};

std::atomic<Node*> head;

Part A — ABA Problem
	1.	Explain what the ABA problem is in the context of this stack.
	2.	Give a concrete interleaving of two threads that leads to ABA.
	3.	Why does CAS fail to detect this bug?

⸻

Part B — Why ABA is Dangerous
	4.	What kind of bugs can ABA cause?
	•	Memory corruption?
	•	Lost updates?
	•	Use-after-free?
	5.	Why is ABA more common on lock-free structures than lock-based ones?

⸻

Part C — Hazard Pointers
	6.	What is a hazard pointer?
	7.	How does it prevent ABA without using locks?
	8.	Describe the exact algorithmic steps for:
	•	Publishing a hazard pointer
	•	Safely reclaiming memory

⸻

Part D — Compare Solutions (Very Important)
	9.	Compare these ABA mitigation techniques:
	•	Tagged pointers
	•	Hazard pointers
	•	Epoch-based reclamation
	•	Reference counting
When would you choose hazard pointers?

⸻

Part E — System-Level Tradeoffs
	10.	What are the performance costs of hazard pointers?
	11.	Why are hazard pointers preferred in kernel / RTOS / low-latency systems?
	12.	How many hazard pointers per thread are typically needed and why?
*/