/*
Question

Consider the following C++ code:

#include <iostream>
#include <vector>
using namespace std;

class Buffer {
public:
    int* data;
    size_t size;

    Buffer(size_t s) : size(s) {
        data = new int[s];
        cout << "Constructor\n";
    }

    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];
        copy(other.data, other.data + size, data);
        cout << "Copy Constructor\n";
    }

    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Move Constructor\n";
    }

    ~Buffer() {
        delete[] data;
    }
};

Buffer createBuffer() {
    Buffer b(100);
    return b;
}

int main() {
    Buffer b1 = createBuffer();
    Buffer b2 = b1;
    Buffer b3 = std::move(b1);
}


⸻

Tasks
	1.	Identify lvalues and rvalues in this code
Ans:
lvalue ->  Buffer(const Buffer& other) 
rvalue -> Buffer(Buffer&& other)
	2.	List the constructors called, in order
Ans:
    Buffer(size_t s) 
    Buffer(const Buffer& other) 
    Buffer(Buffer&& other) 

	3.	Explain why std::move does not move by itself
Ans:
memory allocated by heap wouldn't copy. 
	4.	What is the state of b1 after std::move(b1)?
Ans:
b1 will be NULL data. All the data will be stealed by b3
	5.	What would change if the move constructor were removed?
Ans:
Memory alloacated by heap "data = new int[size];" would not be deep copy. Same data will be pointed for b3.

⸻

Follow-ups Interviewers Love
	•	Why must move constructors usually be marked noexcept?
Ans:
- To indicate compiler not to throw error.
	•	What happens if you use b1 after it is moved from?
Ans:
- It is considered as Use after free. Undefined behaviour
	•	Does return value optimization (RVO) affect this example?
Ans: Yes, temperorary memory can be optimized.
- 
	•	Difference between T&& and forwarding reference?
Ans: Forwarding reference usually used in template. (To preserve the data type)
	•	How is move semantics different from copy-on-write?
Ans:
Move does stealing. Original value will be deleted/Null.
Copy on write, original value is preserved.
- 
*/