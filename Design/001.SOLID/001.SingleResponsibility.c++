#include<iostream>
using namespace std;
struct Myclass{

    public:
    int data;
    Myclass(){
        cout << "Constrcutor" << endl;
    };
    ~Myclass(){
        cout << "Desstrcutor" << endl;
    };
};

int main(){
    // Myclass myclass;
    Myclass *myclass = new Myclass();
    myclass->data = 1;
    delete(myclass);
    return 0;
};