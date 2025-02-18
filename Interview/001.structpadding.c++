#include<iostream>
using namespace std;
//#pragma pack(1)
int main(){
    cout << " padding " << endl;

    struct {
    char a;
    char b;
    int i;
    char c;

    }__attribute__((packed)) something;

    
    cout <<  sizeof(something)<< endl;
    return 0;
}
