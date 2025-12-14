#include<iostream>
#include <vector>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<functional>
#include<chrono>

using namespace std;

struct Elevator{
    bool running;
    int id;
    int curr_floor;
};

class ThreadPool {
private:
    int N;
    vector<thread> threadList;
    queue<function<void()>> tasks;
    mutex m;
    condition_variable cv;
    bool stop;

    void workerPool() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> ul(m);
                cv.wait(ul, [&] {
                    return stop || !tasks.empty();
                });

                if (stop && tasks.empty())
                    return;

                task = tasks.front();
                tasks.pop();
            }
            task();
        }
    }

public:
    ThreadPool(int n) : N(n), stop(false) {
        for (int i = 0; i < N; i++) {
            threadList.emplace_back(&ThreadPool::workerPool, this);
        }
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> ul(m);
            stop = true;
        }
        cv.notify_all();
        for (auto &t : threadList) {
            if (t.joinable()) t.join();
        }
    }

    void submitTask(function<void()> task) {
        {
            unique_lock<mutex> ul(m);
            tasks.push(task);
        }
        cv.notify_one();
    }
};

class ElevatorManager {
private:
    int N;
    int min_f, max_f;

    vector<Elevator> elevatorList;
    mutex elevatorMutex;
    condition_variable cv;

    ThreadPool t_pool;
    int curr_running;

public:
    ElevatorManager(int n, int minF, int maxF)
        : N(n), min_f(minF), max_f(maxF), t_pool(n), curr_running(0) {

        for (int i = 0; i < N; i++) {
            elevatorList.push_back({false, i, min_f});
        }
    }

    Elevator* selectChosen() {
        unique_lock<mutex> lock(elevatorMutex);

        cv.wait(lock, [&] {
            return curr_running < N;
        });

        for (auto &e : elevatorList) {
            if (!e.running) {
                e.running = true;
                curr_running++;
                return &e;
            }
        }

        return nullptr; // logically unreachable
    }

    void move(int start_floor, int end_floor) {
        if (end_floor > max_f || end_floor < min_f)
            return;

        // BLOCKS caller, NOT thread pool
        Elevator* chosen = selectChosen();

        function<void()> task = [=, this] {
            // Move to start
            this_thread::sleep_for(chrono::milliseconds(2000));
            {
                unique_lock<mutex> lock(elevatorMutex);
                chosen->curr_floor = start_floor;
            }

            // Move to end
            this_thread::sleep_for(chrono::milliseconds(2000));
            {
                unique_lock<mutex> lock(elevatorMutex);
                chosen->curr_floor = end_floor;
                chosen->running = false;
                curr_running--;
            }

            cv.notify_one();
        };

        t_pool.submitTask(task);
    }
};



int main(){
    return 0;
}