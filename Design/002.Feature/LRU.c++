#include<iostream>
#include<unordered_map>

using namespace std;

struct node{
    int key;
    int data;
    node* next;
    node* prev;
};

class LRUCache {
public:

    unordered_map<int, node*> map_;
    node* head;
    node* tail;
    int size;
    LRUCache(int capacity) {
        size = capacity;
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
        head->prev = NULL;
        tail->next = NULL;
    }

    void addhead(node* n){
        node* mid = head->next;
        n->next = mid;
        n->prev = head;
        head->next = n;
        mid->prev = n;
    }

    node* remove(int key){
        node* midNode = map_[key];
        midNode->prev->next = midNode->next;
        midNode->next->prev = midNode->prev;
        return midNode;
    }

    void removeTail(){
        if (size == 0)
            return;
        node* lastNode = tail->prev;
        map_.erase(lastNode->key);
        lastNode->prev->next = tail;
        tail->prev = lastNode->prev;
        delete(lastNode);
    }
    
    int get(int key) {
        node* n = map_[key];
        // remove node and add on head
        if(map_.count(key) == 0)
            return -1;
        remove(key);
        addhead(n);
        return n->data;
    }
    
    void put(int key, int value) {
        // add node on head if not present
            // --> if size < capacity --> just add 
            // --> else (size == capacity) --> remove last node
        // remove from middle and add on head

        if(map_.count(key) == 0){
            if(size == map_.size()){
                removeTail();
            }
            node* n = new node;
            n->key = key;
            n->data = value;
            map_[key] = n;
            addhead(n);
        }
        else{
            node* n = map_[key];
            n->data = value;
            remove(key);
            addhead(n);
        }
    }
};


int main(){
    return 0;
}