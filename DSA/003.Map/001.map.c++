#include<iostream>
#include<map>
using namespace std;

int main(){
    map<string , int> m;
    m["A"] = 1;
    m["B"] = 2;

    bool exits = (m.find("AA") != m.end())? true : false;
    cout << exits << endl;
         exits = (m.find("A") != m.end())? true : false;
    cout << exits << endl;
         exits = (m.find("B") != m.end())? true : false;
    cout << exits << endl;
    // cout << m["A"] << endl;
    // cout << m["B"] << endl;

    map<string , int>::iterator it = m.begin();
    

    for(  ;it != m.end(); it++){
        cout << it->first << " " << it->second << endl;
        // std::cout << (*it).first << " " << (*it).second << std::endl;
    }
 
    return 0;
}