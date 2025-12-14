/*

You are given the head of a singly linked list and an integer k.
You must:
Reverse the first k nodes
Skip the next k nodes (leave them unchanged)
Reverse the next k nodes
Skip the next k
… continue this pattern until the list ends.
All reversals must be in-place with O(1) extra space.
Example Input
List:
1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 11 → 12
k = 3
Expected Output
3 → 2 → 1 → 4 → 5 → 6 → 9 → 8 → 7 → 10 → 11 → 12
Explanation
Reverse first 3 → 3 2 1
Skip next 3 → 4 5 6
Reverse next 3 → 9 8 7
Skip next 3 → 10 11 12
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

void reverseUptoX(Node* head, Node* tail){
    cout << tail->val << endl;

    Node* p = head;
    Node* q = head->next;
    

    p->next = NULL;

    while(q != NULL){
        Node* r = q->next;
        q->next = p;
                if(q == tail)
            break;
        p = q;
        q = r;
    }

    // tail->next = p;
    tail = head;
    head = p;
    // print(head);
}

Node* ReverseFirstK(Node* head, int k){
    bool headSelect = false;
    Node* p = head;
    Node* q = head;
    Node* r;

    while(p != NULL){
        // 1 2
        cout << "p  " << endl;
        print(p);
        cout << "q  " << endl;
        print(q);
        for(int i = 0; i < k - 1 && q!=NULL &&  q->next != NULL; i++){
            q = q->next;
        }
        Node* nextSet = q->next;
        reverseUptoX(p, q);
        if (r == NULL){
            p->next = nextSet;
        }
        else{
            r->next = q;
        }

        if(!headSelect){
            headSelect = true;
            head = q;
            // print(head);
        }

        cout << "p-  " << endl;
        print(p);
        cout << "q-  " << endl;
        print(q);

        p = nextSet;
        q = p;

        if(q == NULL){
            p = q;
            break;
        }

        q = q->next;
        p = q;

        for(int i = 1; i < k -1 && q!=NULL &&  q->next != NULL; i++){
            q = q->next;
        }

        if(q == NULL){
            p = q;
            break;
        }
        r = q;
        q = q->next;
        p = q;
    }
    return head;
}

int main(){
    // Node* head = NULL;
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
    head->next->next->next->next->next->next = new Node();
    head->next->next->next->next->next->next->val = 7; 
    head->next->next->next->next->next->next->next = new Node();
    head->next->next->next->next->next->next->next->val = 8; 
    head->next->next->next->next->next->next->next->next = new Node();
    head->next->next->next->next->next->next->next->next->val = 9; 

    

    print(head);

    head = ReverseFirstK(head, 3);
    print(head);
    return 0;
}