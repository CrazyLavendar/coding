#include <iostream>
#include <math.h>

using namespace std;

class Algo{
public:
    static int mul(int x, int y){
        return x * y;
    }
    static int add(int x, int y){
        return x + y;
    }
};

class MathEvent{
public:
    //typedef int(*Callback)(int, int);
    using Callback = int(*)(int, int);
    int triggerCallback(Callback cb, int x = 5, int y = 100){
        return cb(x,y);
    }
private:
    Callback callback;
};

int main(){

    MathEvent event;
    cout << event.triggerCallback(Algo::add, 3,4) << endl;
    cout << event.triggerCallback(Algo::mul, 3,4) << endl;

    cout << event.triggerCallback(Algo::add) << endl;
    cout << event.triggerCallback(Algo::mul, 3) << endl;

    auto val = [&] (in)

    return 0;
}