#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
using namespace std;

int N = 4;

class ThreadPool{
public:
    ThreadPool(int size){
        this->size = size;
        stop = false;
        for(int i = 0; i < size; i++){
            threads.emplace_back(&ThreadPool::workerPool , this, i);
        }
    }
    ~ThreadPool(){
        stop = true;
        cv.notify_all();
        for(int i = 0; i < size; i++){
            threads[i].join();
        }
    }
    void addTask(function<void()> task){
        unique_lock<mutex> ul(m);
        taskQ.push(std::move(task));
        cv.notify_one();
    }
private:
    void workerPool(int id){
        while(true){
            function<void()> task;
            {
                unique_lock<mutex> ul(m);
                cv.wait(ul, [&]{
                    return stop || !taskQ.empty();
                });

                if(stop)
                    return;
                task = std::move(taskQ.front());
                taskQ.pop();
            }
            task();
        }
    }
    int size;
    vector<thread> threads;
    queue<function<void()>> taskQ;
    mutex m;
    condition_variable cv;
    bool stop;
};


void helper(const vector<vector<int>>& A,
            const vector<vector<int>>& B,
            vector<vector<int>>& C,
            int i, int j)
{
    int sum = 0;
    for (int k = 0; k < N; ++k) {
        sum += A[i][k] * B[k][j];
    }
    C[i][j] = sum;
}

vector<vector<int>> Mul(vector<vector<int>>& A, vector<vector<int>>& B) {
    

        vector<vector<int>> res(N, vector<int>(N, 0));
        ThreadPool T(N/2);
        for (int i = 0; i < N; i++) {
            T.addTask([&A, &B, &res, i]{
            for (int j = 0; j < N; j++) {
                        helper(A, B, res, i, j);

                    }
            });
            }

            return res;
    }
        // pool destructor waits for all tasksQ


void fillMat(vector<vector<int>>& arr) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i].push_back((i + 1) * (j + 1));
        }
    }
}

void print(const vector<vector<int>>& arr) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> A(N);
    vector<vector<int>> B(N);
    fillMat(A);
    fillMat(B);

    cout << "printing A" << endl;
    print(A);
    cout << "printing B" << endl;
    print(B);

    vector<vector<int>> C = Mul(A, B);
    cout << "printing C" << endl;
    print(C);

    return 0;
}