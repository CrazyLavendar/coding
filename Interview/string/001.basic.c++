#include<iostream>
using namespace std;

int main(){

    string a = "124";
    string b("Hello"); 

    char *c1 = &b[0];
    char c2[b.length()];
    c2 = c1;


    cout << c1 << endl;

    return 0;
}
