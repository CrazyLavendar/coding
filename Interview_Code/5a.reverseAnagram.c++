/*
Find All Anagram Indices in a String
Given a string s and a pattern p, return all starting indices in s where the substring is an anagram of p.
Example:
Input:
s = "cbaebabacd"
p = "abc"

Output:
[0, 6]

c b a e b a b a c d
0 1 2 3 4 5 6 7 8 9 
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>


using namespace std;

vector<int> anagramIndex(string& s, string& p){
    vector<int> res;
    vector<int> p_alp;
    p_alp.resize(26, 0); // assuming for only lower case alphabets
    unordered_map<char , int> map_;
    int m = s.size(), n = p.size();
    for(char c : p){
        p_alp[c - 'a']++;
    }

    int curr_extra = 0, curr = 0;
    // not possible
    if(n > m)
        return res;

    
    for(int i =0; i < n; i++){
        char c = s[i];
        if(p_alp[c - 'a'] > 0){
            map_[c]++;
            curr++;
            if(map_[c] > p_alp[c - 'a'])
                curr_extra++;
        }
    }

    if(curr_extra == 0 && curr == n){
        res.push_back(0);
    }

    for(int i = n; i < m; i++){
        char curr_c = s[i];
        char prev_c = s[i-n];

        // if present
        if(p_alp[prev_c - 'a'] > 0){
            // reduce extras
            if(map_[prev_c] > p_alp[prev_c - 'a'])
                curr_extra--;
            // reduce map
            map_[prev_c]--;
            // reduce curr
            curr--;
        }

        if(p_alp[curr_c - 'a'] > 0){
            // add map
            map_[curr_c]++;
            // radd curr
            curr++;
            // add extras
            if(map_[curr_c] > p_alp[curr_c - 'a'])
                curr_extra++;
        }


        if(curr_extra == 0 && curr == n){
            res.push_back(i-n+1);
        }
    }

    return res;
}

int main(){
    string s = "cbaebabacd";
    string p = "abc";
    vector res = anagramIndex(s, p);

    for(auto& x : res)
        cout << x << " ";
    cout << endl;

    s = "cbaebabacdabc";
    p = "abc";
    res = anagramIndex(s, p);
    for(auto& x : res)
        cout << x << " ";
    cout << endl;

    s = "abababab";
    p = "ab";
    res = anagramIndex(s, p);
    for(auto& x : res)
        cout << x << " ";
    cout << endl;

    return 0;
}