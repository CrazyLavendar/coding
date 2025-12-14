#include<mutex>
#include<iostream>
#include<queue>
#include<condition_variable>
#include<thread>
#include<atomic>

using namespace std;
int count_ = 0;

struct myData{
    int val;
};

class ProducerConsumer_AtomicBased {
public:
    ProducerConsumer_AtomicBased() {
        N = 10;
        buff.resize(N);
    }

    bool try_push() {
        // Producer must "acquire" the latest tail value to avoid overrunning buffer.
        while ((head.load(memory_order_relaxed) - 
                tail.load(memory_order_acquire)) >= N) 
        {
            this_thread::yield();
        }
        return true;
    }

    bool try_pop() {
        // Consumer must "acquire" the latest head value to avoid reading empty slot.
        while (head.load(memory_order_acquire) == 
               tail.load(memory_order_relaxed)) 
        {
            this_thread::yield();
        }
        return true;
    }

    void producer(int id) {
        while (try_push()) {

            // Producer does NOT need acquire for reading its own head.
            int head_ = head.load(memory_order_relaxed);

            myData b;
            b.val = c++;
            buff[head_ % N] = b;

            cout << " producer pushed val " << b.val << endl;

            // Publish data to consumer
            head.store(head_ + 1, memory_order_release);

            if (b.val == N * N)
                break;
        }
    }

    void consumer(int id) {
        while (try_pop()) {

            // Consumer loads tail with relaxed (own index)
            int tail_ = tail.load(memory_order_relaxed);

            // Safe: acquire was done in try_pop()
            myData b = buff[tail_ % N];

            cout << " consumer consumed val " << b.val << endl;

            tail.store(tail_ + 1, memory_order_release);

            if (b.val == N * N)
                break;
        }
    }

private:
    atomic<int> c{0};       // FIXED: initialize counter
    atomic<int> head{0};    // producer writes, consumer reads
    atomic<int> tail{0};    // consumer writes, producer reads
    vector<myData> buff;
    int N;
};

class ProducerConsumer_MutexBased{
public:

void producer(int id){
    // cout << "producer" << endl;
    while(true){
        unique_lock<mutex> ul(m);
        cv_prod.wait(ul, [&]{
            return q.size() <= size;
        });
        myData data;
        data.val = count_++;
        cout << "producer produced data " << data.val << endl;
        q.push(data);
        cv_cons.notify_one();
        if (data.val == size * size)
            break;
    }
}

void consumer(int id){
    // cout << "consumer" << endl;
    while(true){
        unique_lock<mutex> ul(m);
        cv_cons.wait(ul, [&]{
            return !q.empty();
        });
        myData data = q.front();
        q.pop();
        cout << "consumer consumed data " << data.val << endl;

        cv_prod.notify_one();
        if (data.val == size * size)
            break;
    }
}
    
private:
int size = 10;
mutex m;
condition_variable cv_prod, cv_cons;
queue<myData> q;
};

int main(){
    // ProducerConsumer_MutexBased pc;
    // thread t1(&ProducerConsumer_MutexBased::producer, &pc, 1);
    // thread t2(&ProducerConsumer_MutexBased::consumer, &pc, 2);
    // t1.join();
    // t2.join();

    ProducerConsumer_AtomicBased pc;
    thread t1(&ProducerConsumer_AtomicBased::producer, &pc, 1);
    thread t2(&ProducerConsumer_AtomicBased::consumer, &pc, 2);
    t1.join();
    t2.join();

    return 0;
}