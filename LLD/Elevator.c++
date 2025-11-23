#include<iostream>
#include<vector>
#include<unistd.h>
#include<thread>
#include<cmath>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;
int Elevator_Count = 6;
int low = -3, high = 12; // Floor range
int available_lifts = Elevator_Count;

class Elevator{
    public:
    int index;
    int floor;
    atomic<bool> idle;
};

class ElevatorManager{
private:
    // ElevatorManager  (const ElevatorManager*) = delete;
    // ElevatorManager& operator = (const ElevatorManager&) = delete;
    vector<Elevator*> elevators;
    ElevatorManager(){
        ins_name = "singeton";
        for(int i = 0 ; i < Elevator_Count; i++){
            Elevator* e = new Elevator();
            e->index = i;
            e->floor = 0;
            e->idle = true;
            elevators.push_back(e);
        }
    };
public:
    string ins_name;
    static ElevatorManager* getInstance(){
        static ElevatorManager* instance = new ElevatorManager();
        return instance;        
    }
    Elevator* getNearestIdleElevator(int currFloor){
        Elevator* e;
        unique_lock<mutex> ul(m);
        cv.wait(ul, [] {
            return
            available_lifts > 0 ? true : false;
        });
        int diff = high - low;
        static ElevatorManager* ins = getInstance();
        if(NULL != ins){
            for(Elevator* elevator : ins->elevators){
            	// cout << "loop " << elevator->index << endl;
                if (elevator->idle == false) continue;
                if (elevator->idle == true &&
                    diff > abs(currFloor - elevator->floor))
                {
                    diff = abs(currFloor - elevator->floor);
                    e = elevator;
                }
            }
        }
        return e;
    }
    void setFloor(int curr, int floor){
        Elevator* e = getInstance()->getNearestIdleElevator(curr);
        m.lock();
        e->idle = false;
        available_lifts--;

        cout << " ELevator NO " << e->index << " curr floor" << curr << " and moving to floor " << floor << "\n" << endl;
        m.unlock();
        sleep(3 * abs(floor - e->floor));
        m.lock();
        e->floor = floor;
        cout << " ELevator NO " << e->index << " reached floor " << floor << "\n" << endl;
        e->idle = true;
        if (available_lifts == 0){
            available_lifts++;
            cv.notify_all();
        }
        else
        {
            available_lifts++;
        }
        m.unlock();
    }
};


int main(){

    // cout << ElevatorManager::instance->ins_name << endl;
    ElevatorManager* ins = ElevatorManager::getInstance();


    thread t1(&ElevatorManager::setFloor, ins, 10,  1);
    thread t2(&ElevatorManager::setFloor, ins, 9,  5);
    thread t3(&ElevatorManager::setFloor, ins, 8,  1);
    thread t4(&ElevatorManager::setFloor, ins, -2,  5);
    thread t5(&ElevatorManager::setFloor, ins, 10,  1);
    thread t6(&ElevatorManager::setFloor, ins, 9,  5);
    thread t7(&ElevatorManager::setFloor, ins, 8,  1);
    thread t8(&ElevatorManager::setFloor, ins, -2,  5);
    // ins->setFloor(e, 3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    return 0;
}