#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

class TicketLock{
    mutex m;
    int id;

    void ticketId(int &getId){
        unique_lock<mutex> ul(m);
        id++;
        getId = id;
    }

};

int main(){



    return 0;
}