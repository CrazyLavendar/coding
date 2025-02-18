#include <iostream>
using namespace std;

char* func(){

//  char name[] = "name";
char *name = (char*) malloc (sizeof (5*1));
static char temp[] = "name";
name = temp;
// cout << sizeof(name) << endl;
cout << (char*) name << endl;
return (char*)name;
}

int main() {

    char *ptr = func();
    cout << (char *)ptr << endl;

    return 0;
}