#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;
int amount = 0;
mutex m;
condition_variable cv;
void debit();
void credit();

int main(){

    thread t1 (debit);
    thread t2 (credit);
    t1.join();
    t2.join();

    return 0;
}

void credit(){
    cout << " credit fun" << endl;
    m.lock();
    amount += 500;
    m.unlock();
    if(amount > 0){
        cv.notify_one();
    }
    cout << " amount credit end" << endl;
}


void debit(){
    cout << " debit fun" << endl;
    {
    unique_lock<mutex> ul(m);
    cv.wait(ul , [] {
        return
        amount <= 0?
            false : true;
        }
    );
    }
    if(m.try_lock()){
        cout << "mutex is unloacked" << endl;
    }
    cout << " amount can debit" << endl;
}