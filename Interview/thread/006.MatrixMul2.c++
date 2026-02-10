#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

class ThreadPool{
    mutex m;
    vector<thread> threads;
    bool end;
    condition_variable cv;
    queue<function<void()>> tasks;
public:
    ThreadPool(int numThreads){
        end = false;
        for(int i = 0; i < numThreads; i++){
            threads.emplace_back(&ThreadPool::workerPool, this);
        }
    }
    
    ~ThreadPool(){
        {
            lock_guard<mutex> l(m);
            end = true;
            cv.notify_all();
        }
        for(int i = 0; i < threads.size(); i++){
            threads[i].join();
        }
    }
    
    void SubmitTask(function<void()> task){
        lock_guard<mutex> l(m);
        tasks.push(task);
        cv.notify_one();
    }
    
    void workerPool(){
        while(true){
            function<void()> task;
            {
                unique_lock<mutex> ul(m);
                cv.wait(ul, [&]{
                   return !tasks.empty()  || end;
                });
                
                if(end){
                    cv.notify_all();
                    break;
                }
                
                task = tasks.front();
                tasks.pop();
            }
            task();
        }
    }
    
};

/*
123. 123
456. 456
789. 789

1*1 + 2*4 + 3*7

*/

class MatrixMul{
    vector<vector<int>> A, B, C;
    int n;
    ThreadPool* tPool;
    
public:
    MatrixMul(int N){
        n = N;
        tPool = new ThreadPool(N);
        A.resize(N);
        B.resize(N);
        C.resize(N);
        for(int i = 0; i < N; i++){
            A[i].resize(N);
            B[i].resize(N);
            C[i].resize(N);
        }
        
        fillArr();
        mul();
    }
    
    void fillArr(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                A[i][j] = i+j+1;
                B[i][j] = i+j+1;
            }
        }
    }
    
    int helper(int i, int j){
        int res = 0;
        for(int k = 0; k < n; k++){
            res += A[i][k] * B[k][j];
        }
        return res;
    }
    
    void print(vector<vector<int>>& arr){
        for(auto& row : arr){
            for(int x : row){
                cout << x << " " ;
            }
            cout << endl;
        }
    }
    
    void mul(){
        int remainingTasks = n * n;
        mutex doneMutex;
        condition_variable doneCv;
        print(A);
        print(B);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int row = i;
                int col = j;
                tPool->SubmitTask([&, row, col]{
                    C[row][col] =  helper(row, col);
                    {
                        lock_guard<mutex> lg(doneMutex);
                        remainingTasks--;
                    }
                    doneCv.notify_one();
                });
            }
        }
        
        // Wait for all tasks
        unique_lock<mutex> ul(doneMutex);
        doneCv.wait(ul, [&]{
            return remainingTasks == 0;
        });
        print(C);
    }
};

int main() {

    MatrixMul mul(3);
    return 0;
}