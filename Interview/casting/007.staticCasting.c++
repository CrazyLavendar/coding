#include<iostream>
using namespace std;


int main(){
    cout << "StaticCast" << endl; 

    char c = 10;

    // int *p = static_cast<int*>(&c); -----> static_cast char to int not allowed (Upcast c)

    //char *p = static_cast<char*>(&c); //-----> This is allowed

    int i = 10000000;

    char *p = reinterpret_cast<char*>(&i); // -----> static_cast char to int not allowed (Upcast c)

    cout << *p << endl;


    float f = 10.12345;

    int iF = static_cast<int>(f);

    

    return 0;
}