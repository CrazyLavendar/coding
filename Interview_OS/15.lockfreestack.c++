/*
📌 Interview Question — Lock-Free Stack

Question

Design and implement a lock-free stack supporting the following operations:

void push(int x);
bool pop(int& result);

Requirements
	•	Must be lock-free (no mutex, no condition_variable)
	•	Use atomic operations only
	•	Stack must be thread-safe
	•	Avoid data races and corruption
	•	Handle ABA problem
	•	Should work correctly under high contention

⸻

Follow-ups Interviewers Love
	1.	What makes an algorithm lock-free vs wait-free?
	lock-free uses contionous spinning logic in loop. Consumes more CPU cycles. 
	whereas wait-free using thread sleep logic until the condition met. Busy waiting is avoided.
	2.	Why is compare_exchange essential here?
	compare_exchange is used for ordering the instructions atomically. Updating the top values atomically, compare_exchange is  essential.
	3.	What is the ABA problem, and how do you fix it?
	When thread 1 updates "value A" to "value B" and then back to "value A".
	Thread B sees "value A" but acknowledges "value B" update and back to "value A". 
	Fix ABA problem.
	-a) avoid updating A->B->A in same thread.
	-b) Use seq_cst ordering A->B->A updates
	4.	How does this differ from a mutex-based stack?
	mutex-based stack uses thread sleep logic until the condition met. Busy waiting is avoided.
	5.	What memory ordering is required and why?
	When two threads push/pop stack, ordering is required to protect atomicity.
*/

#include<iostream>
#include<atomic>
#include<vector>
#include<thread>

using namespace std;

class LockFreeStack{
public:
	LockFreeStack(int capacity) : N{capacity}{
		top.store(0);
		myStack.resize(N);
	}
	bool pop(int& result){
		if (try_pop(result)){
			return true;
		}
		else{
			result = -1;
			cout << "Unable to pop, stack is empty result " << result << endl; 
			return false;
		}
	}
	void push(int x){
		if(try_push(x)){
			// success
			return;
		}
		else{
			cout << "Unable to push, stack is full " << endl; 
		}
	}
private:
	bool try_push(int val){
		if(top.load() == N){
			return false;
		}
		int expected = top.load();
		int next = expected + 1;
		while(true){
			if(top.compare_exchange_weak(expected, next, std::memory_order_acq_rel, std::memory_order_relaxed)){
				myStack[next] = val;
				break;
			}
		}
		return true;
	}
	bool try_pop(int& result){
		if (top.load() == 0){
			return false;
		}
		int expected = top.load();
		int next = expected - 1;
		while(true){
			if(top.compare_exchange_weak(expected, next,std::memory_order_acq_rel, std::memory_order_relaxed)){
				result = myStack[expected];
				break;
			}
		}
		return true;
	}
	const int N;
	atomic<int> top;
	vector<int> myStack;
};




int main(){
	return 0;
}