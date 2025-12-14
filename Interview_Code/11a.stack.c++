/*
Design a stack that supports the following operations in O(1) time:
push(x)
pop()
top()
getMin() → returns minimum element in the stack
getSecondMin() → returns second smallest element in the stack
(return -1 if it doesn't exist)
You must implement this using only stacks (no heaps, no arrays, no multisets).
Example
push(5)
push(3)
push(7)
push(3)

Stack = [5, 3, 7, 3]

getMin() → 3  
getSecondMin() → 5     (3 is min, next distinct is 5)

*/





#include<iostream>
#include<set>
#include<map>
#include<stack>

using namespace std;
struct myData{
    int val;
    int count;
};

stack<int> s;
map<int, int> m;

void push(int x){
    m[x]++;
    s.push(x);
}

void pop(){
    int x = s.top();
    s.pop();
    m[x]--;
    if(m[x] == 0){
        m.erase(x);
    }
}

int top(){
    return s.top();
}

int getMin(){
    int ans = -1;
    if(m.size() >= 1){
        ans = m.begin()->first;

    }
    return ans;
}

int getSecondMin(){
    int ans = -1;
    if(m.size() >= 2){
        auto it = m.begin();
        it++;
        ans = it->first;
    }
    return ans;
}

int main(){


    push(3);
    push(3);
    push(7);
    push(5);


    cout << getMin() << endl;
    cout << getSecondMin() << endl;

    pop();
    pop();

    cout << getMin() << endl;
    cout << getSecondMin() << endl;


    return 0;
}
