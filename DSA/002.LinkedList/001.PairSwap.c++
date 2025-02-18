#include<iostream>

struct Node{
    int data;
    Node *next;
};

class MyNode{
public:
    int data;
    MyNode* next;

    // MyNode () : data{0} {}
    MyNode(int data) {
        this->data = data;
    }
    MyNode(int data,MyNode* next) {
        this->data = data;
        this->next = next;
    }

};

int main(){

    /*
    Node* head = (Node*) malloc(sizeof(Node));
    Node* head1 = (Node*) malloc(sizeof(Node));
    Node* head2 = (Node*) malloc(sizeof(Node));
    Node* head3 = (Node*) malloc(sizeof(Node));
    Node* head4 = (Node*) malloc(sizeof(Node));
    // Node* head5 = (Node*) malloc(sizeof(Node));

    head->data = 0;
    head1->data = 1;
    head2->data = 2;
    head3->data = 3;
    head4->data = 4;
    // head5->data = 5;

    head->next = head1;
    head1->next = head2;
    head2->next = head3;
    head3->next = head4;
    // head4->next = head5;
    
    Node *p = head, *q = head->next;
    while(p != NULL && q!= NULL){
        // std::cout << p->data << std::endl;
        int temp = p->data;
        p->data = q->data;
        q->data = temp;
        p = q->next;
        if(p!= NULL)
            q = p->next;
    }
    p = head;
     while(p != NULL){
        std::cout << p->data << std::endl;
        p = p->next;
    }
    */

    MyNode *node5 = new MyNode(5);
    MyNode* node4 = new MyNode(4,node5);
    MyNode* node3 = new MyNode(3, node4);
    MyNode* node2 = new MyNode(2, node3);
    MyNode* node1 = new MyNode(1, node2);

    // MyNode * dummy = new Node();
    MyNode *p = node1, *q = p->next;

    p->next = NULL;
    while (p != NULL && q != NULL){
        // std::cout << p->data << std::endl;
        // p = p->next;
        MyNode *bal = q->next;
        q->next = p;
        p = q;
        q = bal;
    }

     while(p != NULL){
        std::cout << p->data << std::endl;
        p = p->next;
    }
    // MyNode* node2(2,node3);
    // MyNode* node1(1,node2);

    return 0;
}