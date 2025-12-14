/*
Question
You are given the following C++ code that models a bidirectional graph using std::shared_ptr:

#include <iostream>
#include <memory>
using namespace std;

struct Node {
    int val;
    shared_ptr<Node> next;
    shared_ptr<Node> prev;

    Node(int v) : val(v) {}
};

int main() {
    auto n1 = make_shared<Node>(1);
    auto n2 = make_shared<Node>(2);

    n1->next = n2;
    n2->prev = n1;

    return 0;
}


⸻

Tasks
	1.	Why does this program leak memory even though shared_ptr is used?
[Ans:] Both n1 and n2 objects wouldn't be deleted with destrucor.
n1 has shared ownership on n2, and vice versa.

	2.	Explain what the reference counts are just before main() ends.
[Ans:] reference count for n1 and n2 = 2;

	3.	Fix the memory leak using the minimal change (no redesign).
[Ans:] Using weak_ptr for any of prev or next can help.
struct Node {
    int val;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;

    Node(int v) : val(v) {}
};


	4.	What rule should you follow when designing ownership graphs with smart pointers?
[Ans:] Always using unique_ptr , when the resources are not shared
If the reources are shared, use shared + weak pointer to allow resources safe.

⸻

Follow-ups Interviewers Ask
	•	Why doesn’t shared_ptr automatically break cycles?
[Ans:] Shared_ptr doesn't know which one of the object is actual owner. Hence ref count wont reach to zero.
Thus in C++, shared_ptr wont break cycle by itself.
	•	How does weak_ptr differ from shared_ptr internally?
[Ans:] weak_ptr are considered only as observers. 
It is used to break the circular dependency. There is no ownership when weak_ptr is used. (i,e) refernece count doesn't incrment
	•	What happens if you access an expired weak_ptr?
[Ans:] It may be undefined behaviour or NULL.
	•	Can unique_ptr ever cause cycles?
[Ans:] Yes. It wont cause cycle, due to single ownership. Reference count is always 1.

	•	When is it correct to use only shared_ptr?
[Ans:] when thre resources can be shared with multiple same related object.
Eg : reader , writer.
All readers can created with shared pointer.

*/