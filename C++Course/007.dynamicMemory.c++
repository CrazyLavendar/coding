#include<iostream>

#define myNew(type) ((type*)malloc(sizeof(type)))
//#define mySizeof(type) ((char*)(&type+1) -(char*)(&type)) 
using namespace std;

struct s{
    int a;
    float f;
    bool b;
    double d;
};

int main(){
    int* x = myNew(int);
    char* c = myNew(char);
    s *s1 = myNew(s);
    s *s2 = new s;

    s* s3 = nullptr;

    // cout << sizeof(s1) << endl;
    cout << sizeof(&s2) << endl;
    delete(x);
    return 0;
}