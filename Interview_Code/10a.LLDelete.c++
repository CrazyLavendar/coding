/*
Q1. Remove Nth Node From End — but List is Extremely Long
You are given the head of a singly linked list.
Remove the n-th node from the end in one pass, but with a twist:
Twist
The list may contain up to 100 million nodes, so:
You must not store the list in arrays/vectors
You must use O(1) extra space
You must traverse the list only once (no counting first)
Function signature
Node* removeNthFromEnd(Node* head, int n);
Test Case
List: 1 → 2 → 3 → 4 → 5 → 6, n = 3
Output: 1 → 2 → 3 → 5 → 6
(Removed node = 4)

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

Node* removeNthFromEnd(Node* head, int n)
{
    if (n <= 0)
        return NULL;
    Node* p = head;
    Node* q = head;

    int temp = n-1;

    while(q != NULL && temp--){
        q = q->next;
    }

    // cout << "q " << q->val << endl;
    // have to remove head
    if(NULL == q || temp > 0){
        // invalid combination
        return NULL;
    }
    else if(q->next == NULL){
        Node* newHead = head->next;
        delete(head);
        return newHead;
    }


    while(q->next != NULL && q->next->next != NULL){
        p = p->next;
        q = q->next;
        
    }

    Node* removeNode = p->next;
    p->next = removeNode->next;
    delete(removeNode);

    return head;
}



int main(){
    Node* head = new Node();
    head->val = 1;
    head->next = new Node();
    head->next->val = 2;
    head->next->next = new Node();
    head->next->next->val = 3;
    head->next->next->next = new Node();
    head->next->next->next->val = 4;
    head->next->next->next->next = new Node();
    head->next->next->next->next->val = 5;
    head->next->next->next->next->next = new Node();
    head->next->next->next->next->next->val = 6;

    print(head);

    Node* removedHead = removeNthFromEnd(head, 3);
    // cout << rem->val << endl;
    print(removedHead);
    return 0;
}