#include<iostream>
#include<map>
using namespace std;

int SIZE = 4; // cache size

struct Node{
public:
    int data;
    Node* next;
    Node* prev;

    Node(){}
    Node(int data) : data(data){}
};

class Cache{
public:
    virtual void insert(int) = 0; // pure virtual function
};

class LRU : public Cache{
public:
    Node* head;
    Node* tail;
    map<int, Node*> m;

    int currlimit;
    
    LRU() : currlimit(0){
        head = new Node();
        head->data = -1;
        head->prev = NULL;
        head->next = NULL;
        tail = head;
    }

    void SwapToTail(Node* node){
        cout << "trying to swap node data  " << node->data << endl;
        Node* front = head;
        Node* back = node->next;

        front->next = back;
        back->prev = front;

        node->next = NULL;
        node->prev = tail;
        tail->next = node;
        tail = node;
    }

    void insert(int data) override{
        // If cache Has data
        if(m.count(data) > 0){
            SwapToTail(m[data]);
            return;
        }

        // If cache don't have data
        if(currlimit >= SIZE){
            Node* removeNode = head->next;
            removeNode->next->prev = head;
            removeNode->prev->next = removeNode->next;
            delete(removeNode);

        }
        cout << " trying insert on tail data : " << tail->data << " new data : "<<  data << endl;
        Node* newNode = new Node(data);
        newNode->next = NULL;
        newNode->prev = tail;

        tail->next = newNode;
        tail = newNode;
        currlimit++;
        m[data] = tail;
    }

    void traverse(){
        Node* curr = head->next;
        while(NULL != curr){
            cout << " " << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main(){
    // Cache* c;
    // c = new LRU(c);
    LRU* lru = new LRU();
    lru->insert(1);
    lru->insert(2);
    lru->insert(3);
    lru->insert(4);
    lru->insert(5);
    lru->insert(2);
    lru->traverse();

    delete(lru);
    return 0;
}