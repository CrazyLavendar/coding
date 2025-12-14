#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
using namespace std;

int N = 4;

class Threadpool {
public:
    Threadpool(int size) : stop(false) {
        this->size = size;
        for (int i = 0; i < size; i++) {
            threadPoolThreads.emplace_back([this, i]() {
                workerLoop(i);
            });
        }
    }

    ~Threadpool() {
        {
            unique_lock<mutex> ul(mtx);
            stop = true;
        }
        cv.notify_all();

        for (auto &t : threadPoolThreads) {
            if (t.joinable())
                t.join();
        }
    }

    void addTask(function<void()> task) {
        {
            unique_lock<mutex> ul(mtx);
            tasksQ.push(task);
        }
        cv.notify_one();
    }

private:
    void workerLoop(int id) {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> ul(mtx);
                cv.wait(ul, [this]() {
                    return stop || !tasksQ.empty();
                });

                if (stop && tasksQ.empty())
                    return;

                task = tasksQ.front();
                tasksQ.pop();
            }
            task();
        }
    }

public:
    vector<thread> threadPoolThreads;
    mutex mtx;
    condition_variable cv;
    int size;
    bool stop;
    queue<function<void()>> tasksQ;
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

    {
        Threadpool pool(N / 2);  // 2 worker threads for N=4

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                pool.addTask([&A, &B, &res, i, j]() {
                    helper(A, B, res, i, j);
                });
            }
        }
        // pool destructor waits for all tasksQ
    }

    return res;
}

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