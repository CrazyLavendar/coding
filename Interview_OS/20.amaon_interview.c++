// Online C++ compiler to run C++ program online
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;

class Singleton{

private:
int N;
int H;
mutex m;
condition_variable cv_h, cv_s, cv_a;
bool b_h, b_s, b_a;


public:

Singleton(int cap) : N (cap){
    H = 0;
    b_h = true;
    b_s = false;
    b_a = false;
}

// static Singleton* getInstance(int N){
//     static Singleton instance(N);
//     return &instance;
// }

void heartbeat(){
    while(true){
        unique_lock<mutex> ul(m);
        cv_h.wait(ul, [&]{
            return b_h;
        });
        if(H == 2*N){
            cv_h.notify_one();
            cv_a.notify_one();
            cv_s.notify_one();
            break;
        }
        
        H++;
        cout << " Inside heartbeat " << H << endl;
        b_h = false;
        if(H % 2 == 1){
            b_s = true;
            cv_s.notify_one();
        }else {
            b_a = true;
            cv_a.notify_one();
        }
    }  
}
void signal(){
    while(true){
         unique_lock<mutex> ul(m);
        cv_s.wait(ul, [&]{
            return b_s;
        });
        if(H == 2*N){
            cv_h.notify_one();
            cv_a.notify_one();
            cv_s.notify_one();
            break;
        }
        cout << " Inside signal " << H << endl;
        b_s = false;
        b_h = true;
        cv_h.notify_one();    
    }
}
void actuator(){
    while(true){
        unique_lock<mutex> ul(m);
        cv_a.wait(ul, [&]{
            return b_a;
        });
        cout << " Inside actuator " << H << endl;
        
        if(H == 2*N){
            cv_h.notify_one();
            cv_a.notify_one();
            cv_s.notify_one();
            break;
        }
        b_a = false;
        b_h = true;
        cv_h.notify_one();    
    }
}

};

int main(){
    
    Singleton instance(8);
    thread t1(&Singleton::heartbeat, &instance);
    thread t2(&Singleton::signal, &instance);
    thread t3(&Singleton::actuator, &instance);
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}