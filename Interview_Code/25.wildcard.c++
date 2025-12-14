/*
Design a data structure that supports adding and searching words with wildcard support.

Implement the following class:

class WordDictionary {
public:
    WordDictionary();
    void addWord(string word);
    bool search(string word);
};


⸻

Requirements
	•	addWord(word)
Adds a word to the data structure.
	•	search(word)
Returns true if there is any word in the data structure that matches word, otherwise false.
	•	The search word may contain the wildcard character '.' which can match any one letter.

⸻

Constraints
	•	1 ≤ word.length ≤ 25
	•	At most 10⁴ calls to addWord and search
	•	Words contain only lowercase English letters
	•	Must be efficient — Trie-based solution expected

⸻

Examples

addWord("bad")
addWord("dad")
addWord("mad")

search("pad") → false
search("bad") → true
search(".ad") → true
search("b..") → true


⸻

Follow-ups Interviewers Ask
	1.	Why does wildcard search require DFS?
[Ans :] DFS is required to search all possibilities (a to z) 
	2.	What is the time complexity of search() with '.'?
[Ans :] if there is one dot, T.C = (n-1) * 26, 2 dot - > (n - 2) * 26 ^ 2
worst case T.C = O(26 ^ n)
	3.	How would you optimize memory usage?
[Ans :] Currently used Trie data structure. Expecting it is be most optimized.
	4.	Can this be made thread-safe?
[Ans :] Yes. With Readers-Writers concept, this can be made thread-safe.
addWord -> Writer
search -> Multiple readers
	5.	How would you support deletion of words?
[Ans :] Add count as part of Node structure. This can be incrmented based on addWord.
 If count is "zero", Node pointer can deleted.

⸻
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct Node{
    bool end;
    Node* next[26];
};

class WildCard{

private:

Node* head;
int ctoi(char c){
    return c - 'a';
}

void addWord(string s, int index, Node* curr){
    // cout << s << " add " << index << endl;
    if(index == s.size()){
        cout << s << " add " << index << endl;
        curr->end = true;
        return;
    }
    if(nullptr == curr->next[index]){
        int char_ind = ctoi(s[index]);
        curr->next[char_ind] = new Node();
        curr->next[char_ind]->end = false;
        addWord(s, index + 1, curr->next[char_ind]);
    }
}



bool search(string s, int index, Node* curr){
    
    if(index == s.size()){
        // cout << s << " " << index << endl;
        if(curr != NULL && curr->end == true){
            
            return true;
        }
        else{
            return false;
        }
    }
    if(curr == NULL){
        return false;
    }

    bool res = false;

    if(s[index] == '.'){
        for(int i = 0; i < 26; i++){
            res |= search(s, index + 1, curr->next[i]);
        }
    }
    else{
        int char_ind = ctoi(s[index]);
        res |= search(s, index + 1, curr->next[char_ind]);
    }
    return res;
}

public:
WildCard(){
    head = new Node();
    head->end = true;
}
void addWord(string s){
    addWord(s, 0, head);
}
bool search(string s){
    return search(s, 0, head);
}
};


int main(){

    WildCard w;

w.addWord("bad");
w.addWord("dad");
w.addWord("mad");

cout << w.search("pad") << endl;
cout << w.search("bad") << endl;
cout << w.search(".ad") << endl;
cout << w.search("b..") << endl;

    return 0;
}