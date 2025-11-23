/*
Given a string s and an integer k, return the length of the longest substring that contains at most K distinct characters.
Example:
s = "eceba", k = 2 → Output: 3 ("ece")
*/

#include<iostream>
#include<unordered_map>
using namespace std;

struct my_data{
public:
    int ind; // lastIndex
    int count;
};
int LongestSubstring(string s, int k){
    unordered_map<char, my_data> um;
    int ans = 0 , curr = 0, k_ = 0;
    int last_index = 0;
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        // dont disturb
        if(um.count(c) > 0){
            curr++;
            um[c].count++; // store last index in map
            um[c].ind = i;
        }
        else{
            // can add more
            if (k_ < k){
                my_data d; 
                d.ind = i;
                d.count = 1;
                um[c] = d;
                k_++;
                curr++;
            }
            // slide window
            else{
                int j = last_index;
                while(j < i){
                    char x = s[j];
                    if(um[x].count == 1){
                        last_index = j+1;
                        um.erase(x);
                        break;
                    }
                    else{
                        um[x].count--;
                    }
                    j++;
                }

                my_data d; 
                d.ind = i;
                d.count = 1;
                um[c] = d;
                curr = i - last_index + 1;
            }
        }
        ans = max(curr, ans);
    }
    return ans;
}

int main(){

    cout << LongestSubstring("eceba", 2) << endl;
    cout << LongestSubstring("saravanan", 2) << endl;
    cout << LongestSubstring("sree", 2) << endl;
    cout << LongestSubstring("acccc", 2) << endl;
    return 0;
}