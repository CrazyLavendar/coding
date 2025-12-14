#include<iostream>
#include<thread>
#include<memory>
#include<condition_variable>
#include<mutex>
#include<semaphore>
#include<queue>

using namespace std;

int count_ = 1;

struct Buff{
    int data;
};

class ProducerConsumer{
public:
    ProducerConsumer(int n){
        N = n;
    }
    virtual void producer(int id){

    }
    virtual void consumer(int id){

    }
    int N;
};

class MutexBased : public ProducerConsumer{
public:
    // initialize base with provided capacity instead of using uninitialized N
    MutexBased(int n): ProducerConsumer(n) {}
    void producer(int id) override{
        while(true){
            unique_lock<mutex> ul(m);
            cv_prod.wait(ul, [&]{
                return q.size() < N;
            });
            // Critical section
            Buff b;
            b.data = count_++;
            q.push(b);
            cout << " producer pushed data " << b.data << endl;

            // notify others
            cv_cons.notify_one();
            this_thread::yield();
            if (count_ == N*N)
                break;
        }
    }
    void consumer(int id) override {
        while (true)
        {
            unique_lock<mutex> ul(m);
            cv_cons.wait(ul, [&]{
                return q.size() > 0;
            });

            Buff b = q.front();
            cout << " counsumer consumed data " << b.data << endl;
            q.pop();
            cv_prod.notify_one();
            this_thread::yield();

            if (count_ == N*N)
                break;
        }
    }
private:
    mutex m;
    condition_variable cv_prod, cv_cons;
    queue<Buff> q;
};

class SemaphoreBased : public ProducerConsumer{
    public:
        SemaphoreBased(int n): ProducerConsumer(n){}

    void producer(int id) override{
        while(true){
            semaphore.acquire();
            // Critical section
            if (q.size() == N) {
                semaphore.release();
                continue; // avoid deadlock if queue is full
            }
            Buff b;
            b.data = count_++;
            cout << " producer pushed data " << b.data << endl;
            q.push(b);
            if (count_ == N*N)
                break;
            semaphore.release();
        }
    }

    void consumer(int id) override {
        while (true)
        {
            semaphore.acquire();
            if (q.empty()) {
                semaphore.release();
                continue; // avoid deadlock if queue is empty
            }
            Buff b = q.front();
            cout << " counsumer consumed data " << b.data << endl;
            q.pop();
            if (count_ == N*N)
                break;

            semaphore.release();
        }
    }

    private:
        binary_semaphore semaphore{1};
        queue<Buff> q;

};

class AtomicBased : public ProducerConsumer{
public:
    AtomicBased(int n) : ProducerConsumer(n) {
        buff.resize(n);
        c = 1;
    };

bool try_push(){
    while ((head.load(memory_order_relaxed) - tail.load(memory_order_acquire)) >= N ) {
        this_thread::yield();
    }
    return true;
}

// wait until there is data (empty when head == tail)
bool try_pop(){
    while (head.load(memory_order_acquire) == tail.load(memory_order_relaxed) ) {
        this_thread::yield();
    }
    return true;
}

    void producer(int id) override {
        while(try_push()){
            int head_ = head.load(memory_order_acquire);
            Buff b;
            b.data = c++;
            buff[head_ % N] = b;
            cout << " producer pushed data " << b.data << endl;
            head.store(head_ + 1, memory_order_release);

            if (c == N*N)
                break;
        }

    }
    void consumer(int id) override {
        while(try_pop()){
            int tail_ = tail.load(memory_order_acquire);
            Buff b = buff[tail_ % N];
            cout << " counsumer consumed data " << b.data << endl;
            tail.store(tail_ + 1, memory_order_release);
            if (c == N*N)
                break;
        }
    }
private:
    atomic<int> c;
    atomic<int> head{0};
    atomic<int> tail{0};
    vector<Buff> buff;

};

int main(){

    // MutexBased mb(10);
    // SemaphoreBased  mb(10);
    AtomicBased  mb(10);
    
    ProducerConsumer* pc = &mb;
    thread t1(&ProducerConsumer::producer, pc, 1);
    thread t2(&ProducerConsumer::consumer, pc, 2);

    t1.join();
    t2.join();

    return 0;
}