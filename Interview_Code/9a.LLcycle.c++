#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct CycleData{
    int cycleLen;
    Node* start;
};

class LinkedList{
public:
    void print(Node* head){
        while(head != NULL){
            cout << head->data << " -> " ;
            head = head->next;
        }
        cout << endl;
    }
    CycleData getCycleData(Node* head){
        Node* p = head;
        Node* q = head;
        bool isCycle = true;

        do {
            // cout << "1st p : " << p->data << "  q: " << q->data << endl;
            if (NULL == p->next || NULL == q->next || NULL == q->next->next){
                isCycle = false;
                break;
            }
            p = p->next;
            q = q->next->next;
        }while(p != q);

        int count_ = 0;
        //  cout << "  inbet p : " << p->data << "  q: " << q->data << endl;
        CycleData cd;
        //p = head;
        if (isCycle){
            do {
                count_++;
                // cout << "b4 p : " << p->data << "  q: " << q->data << endl;
                p = p->next;
                q = q->next->next;
                // cout << "aftr p : " << p->data << "  q: " << q->data << endl;
            }while(p != q);
            
            cd.cycleLen = count_;
            cd.start = p;
        }
        else{
            cd.cycleLen = 0;
            cd.start = NULL;
        }
        return cd;
    }
private:

};

int main(){

    Node* head = new Node();
    head->data = 1;
    head->next = new Node();
    head->next->data = 2;
    head->next->next = new Node();
    head->next->next->data = 3;
    head->next->next->next = new Node();
    head->next->next->next->data = 4;

    LinkedList ll;
    ll.print(head);
    // cycle
    head->next->next->next->next = head;

    CycleData cd = ll.getCycleData(head);
cout << "cycleLength : " << cd.cycleLen 
     << " Start : "
     << (cd.start == nullptr 
            ? "NULL" 
            : ("Cycle starting node with value " + to_string(cd.start->data)))
     << endl;


    head = new Node();
    head->data = 1;
    head->next = new Node();
    head->next->data = 2;
    head->next->next = new Node();
    head->next->next->data = 3;
    


    ll.print(head);
    // cycle
    // head->next->next->next = head->next;


    cd = ll.getCycleData(head);
cout << "cycleLength : " << cd.cycleLen 
     << " Start : "
     << (cd.start == nullptr 
            ? "NULL" 
            : ("Cycle starting node with value " + to_string(cd.start->data)))
     << endl;
 
    return 0;
}