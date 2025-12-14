/*
Q1. Dynamic Connected Components (Primary Question)

You are given N devices (0…N-1) in a SoC fabric.
Connections between devices are added dynamically.

Implement a system that supports:
	•	connect(u, v)
	•	isConnected(u, v)
	•	countComponents()

Constraints:
	•	N up to 10⁷
	•	Operations up to 10⁷
	•	Must be near O(1) per operation

Explain:
	•	Data structure choice
	•	Optimizations
	•	Memory layout concerns

Expected Direction
	•	Union-Find
	•	Path compression + union by rank/size
	•	Flat arrays (cache friendly)
	•	Avoid recursion
*/
/*
1,2,3,4

1, 2-3-4

0-1 , 2-3 , 4



*/




#include<iostream>
#include<vector>

using namespace std;

struct Node{
    int parent;
    int degree;
};

class ConnectedComp{
private:
    int N;
    int connected;
    vector<Node> arr;
public:
    ConnectedComp(int comp){
        N = comp;
        connected = N;
        for(int i = 0; i < N; i++){
            arr.push_back({i, 1});
        }
    }
    int getParent(int u){
        if(arr[u].parent == u)
            return u;
        return getParent(arr[u].parent);
    }
    void connect (int u, int v){

        if(isConnected(u, v))
            return;

        int pU = getParent(u);
        int pV = getParent(v);
        if (arr[pU].degree < arr[pV].degree){
            int temp = pU;
            pU = pV;
            pV = temp;
        }

        arr[pV].parent = pU;
        arr[pU].degree += arr[pV].degree;
        connected--;
    }
    bool isConnected(int u, int v){
        return getParent(u) == getParent(v);
    }
    int countComponents(){
        return connected;
    }
};

int main(){

ConnectedComp soc(5);
cout << "Initial count: " << soc.countComponents() << endl; // Expected: 5

soc.connect(0, 1);
cout << "Count after connect(0,1): " << soc.countComponents() << endl; // Expected: 4

soc.connect(2, 3);
cout << "Count after connect(2,3): " << soc.countComponents() << endl; // Expected: 3

cout << "isConnected for 0-2: " << (soc.isConnected(0, 2) ? "True" : "False") << endl; // Expected: False

soc.connect(1, 2);
cout << "Count after connect(1,2): " << soc.countComponents() << endl; // Expected: 2

cout << "isConnected for 0-3 (transitive): " << (soc.isConnected(0, 3) ? "True" : "False") << endl; // Expected: True

// Redundant connection test
soc.connect(0, 3);
cout << "Count after redundant connect(0,3): " << soc.countComponents() << endl;
    return 0;
}