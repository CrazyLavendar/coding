#include<iostream>
#include<atomic>
#include<thread>
#include<optional>
#include<vector>

using namespace std;
int N = 10;
// template<typename T>
class SPSC{

public:

    SPSC(int cap){
        capacity = cap;
        buf.resize(cap, 0);
        head.store(0);
        tail.store(0);
    }

    bool try_push(int a){
        int head_ = head.load();
        int next_ = (head + 1);

        if(next_ == tail.load()){
            return false;
        }

        buf[head_] = a;
        head.store(next_);
        return true;
    }
    optional<int> try_pop(){
        int tail_ = tail.load();

        if(tail_ == head.load()){
            return nullopt;
        }

        optional<int> c = buf[tail_];
        tail.store((tail_+1));

        return c;
    } 

private:
    int capacity;
    vector<int> buf;
    atomic<int> head;
    atomic<int> tail;
};

int main(){

    SPSC q(N);

    thread producer([&]{
        for(int i = 0; i < N; i++){
            while (!q.try_push(i)) std::this_thread::yield();
        }
        // mentioning end;
        while (!q.try_push(-1)) std::this_thread::yield();
    });

    thread consumer([&]{
        while(true){
            auto consumed_val = q.try_pop();
            // end
            if(*consumed_val == -1)
                break;

            cout << "consumer consumed " << *consumed_val << endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
