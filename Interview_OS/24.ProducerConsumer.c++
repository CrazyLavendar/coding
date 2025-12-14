#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>


class Solution{

private:

int N;
int curr;
mutex m;
condition_variable cv;
vector<int> buffers;
long id;

public:

    Solution(int N){
        id = 0;
        curr = 0;
        buffers.resize(N, -1);
    }

    void put(int item){
        unique_lock<mutex> ul(m);
        id++;
        curr++;
        cv.wait(ul, [&]{
            return (curr < N); // full
        });

        buffers[(curr - 1) % N] = item; // since array starts 0

        cv.notify_all();
    }

    int get(){
        int res = -1;
        {
            unique_lock<mutex> ul(m);
            cv.wait(ul, [&]{
                return (curr > 0);
            });
            
            res = buffers[(curr - 1) % N];
            curr--;
            cv.notify_all();
        }
        return res;
    }
}

int main(){

    return 0;
}