#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>


class Solution{

private:

int N;
mutex m;
condition_variable cv;
vector<int> buffers;
int head, tail;

public:

    Solution(int N){
        head = 0;
        tail = 0;
        buffers.resize(N, -1);
    }

    void put(int item){
        unique_lock<mutex> ul(m);
        cv.wait(ul, [&]{
            return ((head - tail) < N); // full logic
        });

        buffers[head % N] = item;
        head++; // ready for next

        cv.notify_all();
    }

    int get(){
        int res = -1;
        {
            unique_lock<mutex> ul(m);
            cv.wait(ul, [&]{
                return (head > tail); // has some buffers
            });
            
            res = buffers[tail % N];
            tail++;
            cv.notify_all();
        }
        return res;
    }
}

int main(){

    return 0;
}