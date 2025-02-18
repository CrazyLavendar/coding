#include<iostream>
#include<queue>
using namespace std;

class Compare{

    public:
    bool  operator () (int a, int b) {
        if(a < b)
        return true;
        return false;
    };
};



int main(){

    priority_queue<int, vector<int> , Compare> pq;
    pq.push(5);
    pq.push(1);
    pq.push(100);

    while(!pq.empty()){
        cout << pq.top() << endl;
        pq.pop();
    }

    vector<int> v = {7,2,4,1002};

    sort(v.begin() , v.end(), Compare());

    for( int x : v){
        cout << x  << " " << endl;
    }



    return 0;
}