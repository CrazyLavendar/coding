#include<iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

void print(Node* head){
    while(head != NULL){
        cout << head->data << endl;
        head = head->next;
    }
}

void delLast(Node* head){

    if(head == NULL)
        return;
    if(head->next == NULL){
        delete(head);
        return;
    }

    Node* p = head, *q = head->next;

    while(p!= NULL && q!= NULL){
        
        if(q->next == NULL){
            delete(q);
            p->next = NULL;
            break;
        }
        p = q;
        q = q->next;
    } 


}

int main(){

    Node* node1 = (Node*) malloc (sizeof(struct Node));
    Node* node2 = (Node*) malloc (sizeof(struct Node));
    Node* node3 = (Node*) malloc (sizeof(struct Node));

    node1->data = 1;
    node1->next = node2;

    node2->data = 2;
    node2->next = node3;
    
    node3->data = 3;

    print(node1);
    delLast(node1);
    print(node1);


try {
    int x = 5/0;
}
catch (arithmetic exception) {
  cout << "Access denied - You must be at least 18 years old.\n";
}




    return 0;
}