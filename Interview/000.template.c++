#include<iostream>
#define my_sizeof(var) ((char *)(&var + 1) - (char *)(&var))

using namespace std;

template<typename T>
void print(const T var){
    cout << var << endl;
}
template<typename T>
int mySizeOf(T var){

    T* curr = &var; 
    T* next = &var + 1;

    return (char *)next - (char *)curr;
}

int main(){
    
    print("Helllo");
    print(0.0006f);
    print(122);

    int i = 10;
    cout << mySizeOf(i) << endl;

    struct {
        int x;
        char c;
        int xx;
        char cc;
        int xxx;
        char ccc;
    }__attribute__((packed)) s;

    cout << mySizeOf(s) << endl;
    cout << my_sizeof(s) << endl;



    return 0;
}
