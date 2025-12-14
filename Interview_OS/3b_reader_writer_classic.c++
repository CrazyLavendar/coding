#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono_literals;

mutex rw_mutex;
condition_variable read_cond, write_cond;

int active_readers = 0;
int waiting_writers = 0;
bool writer_active = false;
int data_ = 0;

void reader(int id){
    this_thread::sleep_for(250ms);

    unique_lock<mutex> ul(rw_mutex);
    read_cond.wait(ul, []{
        return !writer_active && waiting_writers == 0;
    });
    ++active_readers;
    ul.unlock();

    // CS: read
    cout << "Reader " << id << " sees data " << data_ << endl;
    this_thread::sleep_for(5000ms);

    ul.lock();
    --active_readers;
    if (waiting_writers > 0 && active_readers == 0) {
        write_cond.notify_one();
    }
    ul.unlock();
}

void writer(int id){
    this_thread::sleep_for(500ms);

    unique_lock<mutex> ul(rw_mutex);
    ++waiting_writers;
    write_cond.wait(ul, []{
        return !writer_active && active_readers == 0;
    });

    --waiting_writers;
    writer_active = true;
    ul.unlock();

    // CS: write
    this_thread::sleep_for(5000ms);
    ++data_;
    cout << "Writer " << id << " updated data_ to " << data_ << endl;

    ul.lock();
    writer_active = false;
    if (waiting_writers > 0) {
        write_cond.notify_one();
    } else {
        read_cond.notify_all();
    }
    ul.unlock();
}

int main(){
    vector<thread> readers;
    vector<thread> writers;

    for (int i = 0; i < 50; i++) {
        if (i % 5 == 0) {
            writers.emplace_back(writer, i / 5);
        }
        readers.emplace_back(reader, i);
    }

    for (auto &t : readers) t.join();
    for (auto &t : writers) t.join();

    return 0;
}