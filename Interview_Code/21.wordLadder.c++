/*
Question

You are given:
	•	beginWord
	•	endWord
	•	a list of words wordList

Each transformation:
	•	changes exactly one character
	•	the transformed word must exist in the word list

Task

Return all shortest transformation sequences from beginWord to endWord.

Each sequence:
	•	starts with beginWord
	•	ends with endWord
	•	consecutive words differ by exactly one character
	•	length of the sequence must be minimal

If no such sequence exists, return an empty list.

⸻

Example

Input

beginWord = "hit"
endWord   = "cog"
wordList  = ["hot","dot","dog","lot","log","cog"]

Output

[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]


⸻

Constraints
	•	1 ≤ wordList.size() ≤ 10⁴
	•	All words have the same length
	•	beginWord may not be in wordList
	•	Must run in O(N × L) where L = word length

⸻

Follow-ups Interviewers Love
	1.	Why does DFS alone fail here?
Need DFS + BFS. BFS is used to get all possible words in each level
	2.	Why must BFS be used first?
To collect all possible words in each level
	3.	How do you avoid revisiting words across levels?
By creating visting uonrdered set in stack.
	4.	How do you reconstruct all paths, not just one?
Current code is constructing all possible path
	5.	What causes TLE in naive solutions?
Visiting the stack again and again.
*/
#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>


using namespace std;

template<typename T>
void print(T t){
    for(auto x : t){
        cout << x << " " ;
    }
    cout << endl;
}

vector<string> possibleStr(int index, string s, unordered_set<string>& set_, unordered_set<string>& vis_){
    vector<string> poss_arr;
    for(int i = 0; i < 26; i++){
        s[index] = 'a' + i;
        if(vis_.count(s) > 0){
            continue;
        }
        else if(set_.count(s) > 0){
            poss_arr.push_back(s);
        }
        // cout << s << endl;
    }
    return poss_arr;
}


void dfs(string end, unordered_set<string>& set_, unordered_set<string>& vis_, vector<string>& res, int index, string curr, string str, unordered_set<string>& stackVis){
    if(index > end.size())
    return;
    
    if(str == end){
        res.push_back(curr);
        return;
    }
    
    vector<string> poss_str = possibleStr(index, str, set_, vis_);
    // print(poss_str);
    if(poss_str.size() == 0)
        return;
    //  cout << " ***** "  << curr  <<" *****" << endl;

    
    vis_.insert(str);
    stackVis.insert(curr);
    // curr += str;
    // cout << str << " ---- " ;
    //print(curr);
    
    for(string s : poss_str){
        if(vis_.count(s)) continue;
        for(int i = 0; i < s.size(); i++){
            
            // curr.push_back(s);
            //vis_.insert(s);
            
            string temp = curr + s;
            if(stackVis.count(temp) > 0)
                    return;
            // stackVis.insert(temp);

            dfs(end, set_, vis_,res, i, temp, s, stackVis);
            // curr.pop_back();
            // stackVis.erase(temp);
            //vis_.erase(s);
        }
    }
    
    vis_.erase(str);
    curr = curr.substr(0, curr.size() - end.size());
    stackVis.erase(curr);


}
vector<vector<string>> solution(string begin, string end, vector<string>& wordList){
    vector<string> res;
    if(begin.size() == 0 || begin.size() != end.size()) return {};

    int n = begin.size();
    // cout << n << endl;

    unordered_set<string> set_, vis_;
    for(string s : wordList){
        set_.insert(s);
    }
    // vis_.insert(begin);
    // vector<string> curr;
    // curr.push_back(begin);
    unordered_set<string> stackVis;

    for(int i = 0; i < begin.size(); i++){
        dfs(end, set_, vis_,res, i, begin, begin, stackVis);
    }

    // unordered_set<string> finalAns;
    // int min_size = 10000000;
    // for(auto a : res){
    //     min_size = min(min_size, a.size)
    // }

    vector<vector<string>> ans(res.size());
    for(int j = 0; j < ans.size(); j++)
    for(int i = 0; i < res[j].size(); i += n){
        ans[j].push_back(res[j].substr(i, n));
    }
    return ans;
}

int main(){
    string beginWord = "hit";
    string endWord   = "cog";
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};

    vector<vector<string>> res = solution(beginWord, endWord, wordList);

    for(auto& row : res){
        for(string s : row){
            cout << s << " ";
        }
        cout << endl;
    }

    return 0;
}