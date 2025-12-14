/*
You are given a list of words from an unknown language, sorted lexicographically according to the rules of that language.

Your task is to determine the order of characters in this alien language.

Requirements
	•	If multiple valid orders exist, return any one
	•	If the order is invalid, return an empty string
	•	Characters are lowercase English letters
	•	Words can have different lengths

Example 1

Input:
["wrt", "wrf", "er", "ett", "rftt"]

Output:
"wertf"

Example 2 (Invalid case)

Input:
["abc", "ab"]

Output:
""

Constraints
	•	1 ≤ number of words ≤ 10⁴
	•	Total characters ≤ 10⁵
	•	Must run in O(V + E)

Follow-ups interviewers ask
	•	How do you detect cycles?
[ans] : Used dfs recursion stack. If stack's index is coming again, cycle present
	•	Why is this a topological sort problem?
[ans] : Characters in alien dictionary sorted lexicographically. lexicographical ordered problems can be solved usually bu topological ordering.
	•	What data structure do you use to build the graph?
[ans] : Used Trie to maintain degree and ordering, Adjacency list for graph to identify topological sort.
	•	How do you handle prefix violations?
[ans] : Stored Degree in Trie , lower the degree is charcter is ascending ordered in alien dict.
This can help in identify prefix and correct ordering.
*/


#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>

using namespace std;



struct Trie{
	int degree;
	vector<int> storeDegree;
	vector<Trie*> next;
	bool end;
};

class Solution {
	private:
	Trie* head;
	bool cycle;
	public:
	Solution(){
		head = new Trie();
		head->next.resize(26);
		head->storeDegree.resize(26);
		head->end = true;
		head->degree = 0;
		cycle = false;
	}

	int ctoi(char c){
		return c -'a';
	}

	char itoc(int i){
		return 'a' + i;
	}

	void insert(Trie* curr, string word, int index){
		if(index == word.size()){
			curr->end = true;
			return;
		}

		if(NULL == curr->next[index]){ // if already not present
			curr->storeDegree[ctoi(word[index])] = ++curr->degree; // increase degree for current node
			Trie* newNode = new Trie();
			newNode->end = false;
			newNode->degree = 0;
			newNode->storeDegree.resize(26);
			newNode->next.resize(26);
			curr->next[index] = newNode;
		}
		// cout << word[index] << endl;
		if(curr->storeDegree[ctoi(word[index])] == 0)
			curr->storeDegree[ctoi(word[index])] = ++curr->degree; // increase degree for current node

		insert(curr->next[index], word, index + 1);
		
	}

	void fillAdj(string& s, vector<unordered_set<int>>& adjList){
		for(int i = 0; i < s.size(); i++){
			for(int j = i + 1; j < s.size(); j++){
				adjList[ctoi(s[i])].insert(ctoi(s[j]));
			}
		}
	}

	void traverse(Trie* head, vector<unordered_set<int>>& adjList){
		
		if(head == NULL || head->degree == 0){
			return;
		}
		int curr_degree = head->degree;

		int start = 1;
		string curr;
		while(curr_degree > 0){
			for(int i = 0; i < 26; i++){
				if(start == head->storeDegree[i]){
					curr += itoc(i);
					start++;
					curr_degree--;
					continue;
				}
			}
		}
		// cout << curr << endl;

		fillAdj(curr, adjList);

		for(int i = 0; i < 26; i++){
			traverse(head->next[i], adjList);
		}

	}


	void dfs(vector<unordered_set<int>>& adjList, string& res, string& curr, int index, vector<int>& vis){

		if(vis[index] == 1 || cycle){
			cycle = true;
			return;
		}

		vis[index] = 1;

		curr += itoc(index);

		if(curr.size() > res.size())
			res = curr;
		
		// cout << res << " " << curr << endl;
	
		for(int x : adjList[index]){
			dfs(adjList, res, curr, x, vis);
		}

		curr.pop_back();
		vis[index] = 2;

	}

    string findOrder(vector<string> &words) {
		// insert
		if(words.size() == 0)
			return 0;

		unordered_set<int> len;
		for(auto& word : words){
			// cout << word << endl;
			for(char c : word){
				len.insert(c);
			}
			insert(head, word, 0);
		}

		// traverse
		vector<unordered_set<int>> adjList(26);
		traverse(head, adjList);
		vector<int> vis(26, 0);
		int startindex = ctoi(words[0][0]);
		string res = "", curr = "";
		dfs(adjList, res, curr, startindex, vis);

		// if cycle or topological sort unable to form
		if(cycle || len.size() > res.size())
			return "";

		return res;

    }
};

int main(){
	
	Solution sol;
	vector<string> arr = {"wrt", "wrf", "er", "ett", "rftt"};
	cout << sol.findOrder(arr) << endl;
	arr = {"abc", "ab"};
	cout << sol.findOrder(arr) << endl;
	return 0;
}