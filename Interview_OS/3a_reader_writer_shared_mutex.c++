#include<iostream>
#include<thread>
#include<mutex>
#include<shared_mutex>
#include<vector>
#include<chrono>

using namespace std;

shared_mutex s_mutex;
int data_ = 0;

void reader(int id){
    // Multiple readers can hold shared_lock at the same time
    shared_lock<shared_mutex> ul(s_mutex);
    this_thread::sleep_for(500ms);

    // CS: safe read
    cout << "Reader " << id << " sees data_ = " << data_ << endl;
}

void writer(int id){
    // Only one writer can hold unique_lock, and it excludes readers
    unique_lock<shared_mutex> ul(s_mutex);

    // CS: safe write
    ++data_;
    cout << "Writer " << id << " updated data_ to " << data_ << endl;
}

int main(){

    vector<thread> readers;
    vector<thread> writers;

    for(int i = 0; i < 50; i++){
        if(i % 5 == 0){
            writers.emplace_back(writer, i / 5);
        }
        readers.emplace_back(reader, i);
    }

    for(auto &t : readers)
        t.join();
    for(auto &t : writers)
        t.join();

    return 0;
}