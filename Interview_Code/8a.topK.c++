/*
You are given an infinite stream of integers.
Support two operations efficiently:
add(x) → adds number x to the stream
topK(k) → returns the k most frequent numbers so far
If frequencies tie → return smaller number first
Must be faster than recomputing from scratch each time
Design and implement the data structure for this.

Q1 test case
Operations:
add(5)
add(1)
add(5)
add(3)
add(5)
add(2)
add(3)
add(3)
topK(2)
add(1)
add(1)
add(1)
topK(3)
Expected Output:
topK(2) → [5, 3]
topK(3) → [1, 5, 3]

*/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<map>
#include<set>
using namespace std;

struct Data_{
    int val;
    int freq;
};

struct Compare{
    bool operator() (Data_ a, Data_ b){
        if (a.freq == b.freq)
            return a.val > b.val;
        else
            return a.freq < b.freq;
    }
};

class TopK{
public:
    void add(int n){
        int prevF = 0, currF = 0;
        if (val_freq.count(n) == 0){
            val_freq[n] = 1;
            prevF = 0;
            currF = 1;
        }
        else{
            prevF = val_freq[n]++;
            currF = val_freq[n];
        }
        // delete
        if (prevF != 0){
            fs[prevF].erase(n);
        }

        // insert
        if (fs.count(currF) == 0){
            set<int> s;
            fs[currF] = s;
        }
        fs[currF].insert(n);
    }
    vector<int> topK(int k){
        vector<int> res;
        auto it = fs.end();
        while(true){
            it--;

            auto values = it->second;
            for(int x : values){
                res.push_back(x);
                if (res.size() == k)
                    break;
            }
            if (res.size() == k)
            break;
            
            if(it == fs.begin())
            break;
        }

        return res;
    }
private:
    map<int, set<int>> fs;
    map<int, int> val_freq;

    
};

void print(vector<int> arr){
    for(int x : arr)
        cout << x << " ";
    cout << endl;
}

int main(){
    TopK t;
    t.add(5);
    t.add(1);
    t.add(5);
    t.add(3);
    t.add(5);
    t.add(2);
    t.add(3);
    t.add(3);
    print(t.topK(2));
    t.add(1);
    t.add(1);
    t.add(1);
    print(t.topK(3));
    return 0;
}
