
/*
You are given two NON-EMPTY linked lists representing two non-negative integers.
Digits are stored in reverse order, as in the classic "Add Two Numbers".
After computing the sum, you must:
Build the resulting list (normal Add Two Numbers)
Reorder the result list in the pattern:
L1 → Ln → L2 → L(n-1) → L3 → L(n-2) → ...
All operations must be in-place, using only O(1) extra memory.
Function signature
Node* addAndReorder(Node* l1, Node* l2);
Example
Input:
l1 = 2 → 4 → 3      (342)
l2 = 5 → 6 → 4      (465)
Steps:
Sum = 342 + 465 = 807
Result list (reverse order): 7 → 0 → 8
Reorder result:
7 → 8 → 0
Output:
7 → 8 → 0
*/


#include<iostream>
using namespace std;

struct Node{
    int val;
    Node* next;
};

void print(Node* head){
    while(head != NULL){
        cout << head->val << " ->";
        head = head->next;
    }
    cout << endl;
}


Node* addNum(Node* A, Node* B){
    Node* C = new Node();
    C->val = -1;
    C->next = NULL;
    int carry = 0;
    Node* curr = C;

    while(A != NULL && B != NULL){
        int num = A->val + B->val + carry;
        curr->next  = new Node();
        curr->next->val = (num % 10);
        carry = num / 10;
        A = A->next;
        B = B->next;
        curr = curr->next;
    }

    while(A != NULL){
        int num = A->val + carry;
        curr->next  = new Node();
        curr->next->val = (num % 10);
        carry = num / 10;
        A = A->next;
        curr = curr->next;
    }

    while(B != NULL){
        int num = B->val + carry;
        curr->next  = new Node();
        curr->next->val = (num % 10);
        carry = num / 10;
        B = B->next;
        curr = curr->next;
    }

    if (carry > 0){
        curr->next  = new Node();
        curr->next->val = carry;
        curr = curr->next;
    }

    return C->next;
}


Node* reverse(Node* head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    Node* p = head;
    Node* q = head->next;
    Node* r = head->next->next;
    p->next = NULL;
    while(true){
        q->next = p;
        // cout << q->val << endl;
        p = q;
        if (r == NULL)
            break;
        q = r;
        r = r->next;
    }
    return p;
}

/*
1 2 3 4 5  6
    p
    q.  q
*/

Node* reorder(Node* head){
    Node* p = head;
    Node* q = head;
    while(q->next != NULL && q->next->next != NULL){
        p = p->next;
        q = q->next->next;
    }
    q = p->next;
    p->next = NULL;
    q = reverse(q);
    p = head;

    while(p != NULL && q != NULL){

        Node* p_ = p->next;
        Node* q_ = q->next;

        p->next = q;
        q->next = p_;

        p = p_;
        q = q_;
    }
    return head;
}

int main(){
    Node* A = new Node();
    A->val = 9;
    A->next = new Node();
    A->next->val = 9;
    A->next->next = new Node();
    A->next->next->val = 9;
    print(A);

    Node* B = new Node();
    B->val = 5;
    B->next = new Node();
    B->next->val = 6;
    B->next->next = new Node();
    B->next->next->val = 4;
    B->next->next->next = new Node();
    B->next->next->next->val = 6;
    B->next->next->next->next = new Node();
    B->next->next->next->next->val = 1;
    B->next->next->next->next->next = new Node();
    B->next->next->next->next->next->val = 9;
    print(B);

    Node* C = addNum(A, B);

    print(C);

    C = reorder(C);

    print(C);

    return 0;
}