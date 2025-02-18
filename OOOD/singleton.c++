#include<iostream>
using namespace std;

class Singleton{

private:

static Singleton *instance; 
Singleton(){
    instance = new Singleton();
    name = "Vimal";
}
public:
// initializing instancePtr with an instance
Singleton *Singleton ::instance = new Singleton(); 
string name;
Singleton(Singleton& obj)  = delete;
static Singleton* getInstance(){
    return instance;
}
};




int main(){

    Singleton* instance1 = Singleton::getInstance();
    // Singleton instance2 = Singleton::getInstance();
    cout << instance1->name << endl;
    // cout << instance2.name << endl;

    // instance2.name = "Kumar";
    // cout << instance1.name << endl;
    // cout << instance2.name << endl;
    cout << "Singleton" << endl;
    return 0;
}