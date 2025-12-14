/*
Design and implement a minimal thread pool in C++ that supports:
	•	Initializing the pool with N worker threads
	•	Submitting tasks (submit(function<void()>))
	•	Graceful shutdown

Constraints
	•	Use only std::thread, std::mutex, std::condition_variable
	•	No busy waiting
	•	Tasks must execute exactly once
	•	Thread pool must be safe under concurrent submissions

Follow-ups (frequently asked)
	1.	How do you avoid lost wakeups?
Ans: need to study
	2.	How do you handle shutdown while tasks are pending?
[Ans] : In current code, destrcutor called early. Since main() executes early. threads will be waiting in join function. Once all the tasks completesd, destructor will be closed.
	3.	How would you support task return values (future)?
[Ans]: Queue can returned with asyn+future mechanism
	4.	What happens if tasks submit other tasks?
[Ans] : It will be continous progress. thread join will never happen and CPU will be busy continously.
	5.	How do you prevent starvation?
[Ans] : Current implementation, starvation can happen. using ticketLock in workerPool(), fairness can be introduced. This can prevent startvation.
*/

#include<iostream>
#include<mutex>
#include<vector>
#include<thread>
#include<condition_variable>
#include<queue>
#include<functional>
#include<chrono>
using namespace std;

class ThreadPool{
public:

ThreadPool(int N) : N{N}{
    stop = false;
    for(int i = 0; i < N; i++){
        threads.emplace_back(&ThreadPool::workerPool, this);
    }
}
~ThreadPool(){
    {
        cout << "called destrcuctor" << endl;
        unique_lock<mutex> ul(m);
        stop = true;
    }
    cv.notify_all();
    for(int i = 0; i < N; i++){
        threads[i].join();
    }
}

void workerPool(){
    while(true){
        function<void()> task;
        {
            cout << "worker loop before mutex" << endl;
            unique_lock<mutex> ul(m);
            cout << "worker loop before cv" << endl;
            cv.wait(ul, [this](){
                return !tasks.empty() || stop;
            });
            cout << "worker loop left task "<< tasks.size() << endl;

            if (stop && tasks.empty()){
                cv.notify_all();
                return;
            }

            task = tasks.front();
            tasks.pop();
        }
        // execute task
        // cout << "perform task" << endl;
        task();
    }
}

void performTask(int index){
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "thread "  << " performs task" << index << endl;
}

void submitTask(int index){
    unique_lock<mutex> ul(m);
    std::function<void()> task = [this, index](){
        performTask(index);
    };
    tasks.push(task);

    cout << "added. task " << index << endl;
    cv.notify_one();
}



private:
    queue<function<void()>> tasks;
    int N;
    mutex m;
    bool stop;
    condition_variable cv;
    vector<thread> threads;
};

int main(){

    ThreadPool threadPool(4);
    for(int i = 0 ; i < 20; i++){
        threadPool.submitTask(i);
    }
    return 0;
}