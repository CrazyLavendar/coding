#include<iostream>
#include<atomic>
#include<vector>

using namespace std;


struct Img{
    int id;
    int data_;
};

class SPSC{

private:
int capacity;
vector<Img> buf_;
atomic<int> head;
atomic<int> tail; 

public:
SPSC(int cap){
    buf_.resize(cap);
}

bool try_push(Img& a){
    int head_ = head.load(memory_order_relaxed);
    int next = (head + 1) % capacity;

    if (next == tail.load(memory_order_acquire)) return false; // if next is with tail

    buf_[head] = a;
    head.store(next, memory_order_release);
    return true;
}

bool try_pop(Img& b){
    int tail_ = tail.load(memory_order_relaxed);
    if (tail_ == head.load(memory_order_acquire)) return false;

    // consume
    b = buf_[tail_];
    tail.store((tail + 1), memory_order_release);
    return true;
}
void producer(){
    int id = 0;
    while(true){
        Img img;
        img.id = id;
        img.data_ = id++;

        while(!try_push(img)){
            // try push
        }
    }
}
void consumer(){
    while (true){
        Img out;
        while(!try_pop(out)){

        }
    }
    
}

};








int main(){
    return 0;
}