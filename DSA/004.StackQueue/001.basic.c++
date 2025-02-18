#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int main(){

    queue<int> q;
    stack<int> s;

    q.push(1);
    q.push(2);
    q.push(3);
      q.push(4);

    s.push(1);
    s.push(2);
    s.push(3);
      s.push(4);

    q.pop();
    s.pop();

    cout << q.front() << endl;
    cout << s.top() << endl;

    // cout << q.back() << endl; /// works
    // cout << s.back() << endl; // not works

    return 0;
}