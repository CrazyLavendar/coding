/*
Problem (Implement a compressed prefix trie / radix trie):
Implement a compressed trie (radix trie) for strings (lowercase a–z) that supports the following operations efficiently:
insert(string s) — insert the string into the trie.
erase(string s) — remove the string if present.
contains(string s) — return true if s exists.
startsWith(string prefix) — return the number of strings in the trie that start with prefix.
longestCommonPrefix() — return the longest common prefix of all strings currently in the trie.
listWithPrefix(string prefix, int limit) — return up to limit strings that start with prefix, in lexicographic order.
Constraints & Requirements
The trie must be compressed (merge single-child chains into edges labeled by strings).
All operations should be asymptotically optimal for a compressed trie (work proportional to length of matched parts, not total tree size).
erase must cleanly remove nodes/edges and re-compress paths where appropriate.
Memory should be compact — avoid storing one character per node when a longer edge label can be used.
Provide amortized complexity reasoning for insert/erase.
Implement edge cases: empty string insertion, duplicate insertions, and removing prefix strings.
Design APIs and explain how you would test for correctness and performance on large datasets (millions of strings).
Follow-ups (interviewer):
Extend to support Unicode (UTF-8) strings — how does your node/edge representation change?
Make listWithPrefix paginated and resilient to concurrent modifications — describe thread-safety or snapshotting strategy.
How would you persist the compressed trie to disk and load it fast (space+IO optimizations)?
*/
#include<iostream>

using namespace std;

struct Node{
    bool end;
    int len;
    Node* next[26];
};

class Trie{
private:
    Node* head;
public:
    Trie(){
        head = new Node();
        head->end = true;
        head->len = 1;
    }
void insert(string s, int index, Node* curr);// — insert the string into the trie.
void insert(string s);// — insert the string into the trie.
void erase(string s, int index, Node* curr);
void erase(string s);// — remove the string if present.
bool contains(string s, int index, Node* curr);
bool contains(string s);// — return true if s exists.
int startsWith(string prefix, int index, Node* curr); 
int startsWith(string prefix); // — return the number of strings in the trie that start with prefix.
void longestCommonPrefix();// — return the longest common prefix of all strings currently in the trie.
void listWithPrefix(string prefix, int limit);// — return up to limit strings that start with prefix, in lexicographic order.
};

void Trie::insert(string s, int index, Node* curr){
    if(index == s.size()){
        if (curr == NULL){
            curr = new Node();
            curr->len = 0;
        }
        curr->end = true;
        return;
    }

    if(curr == NULL){
        curr = new Node();
        curr->len = 0;
        curr->end = false;
    }
    curr->len++;
    int c = s[index] - 'a';
    insert(s, index + 1, curr->next[c]);
}

void Trie::insert(string s){
    insert(s, 0, head);
}

bool Trie::contains(string s, int index, Node* curr){
    if(curr == NULL)
        return false;

    if(index == s.size()){
        if(curr->end)
            return true;
        else
            return false;
    }

    int c  = s[index] - 'a';
    return contains(s, index+1, curr->next[c]);
}
bool Trie::contains(string s){
    return contains(s, 0, head);
}

void Trie::erase(string s, int index, Node* curr){
    if (index == s.size()){
        curr->len--;
        if (curr->len == 0){
            delete curr;
            curr = NULL;
        }
    }
    int c = s[index] - 'a';
    return erase(s, index+1, curr->next[c]);
}

void Trie::erase(string s){
    if (contains(s)){
        erase(s, 0, head);
    }
}

int Trie::startsWith(string prefix, int index, Node* curr){
    if (curr == NULL)
        return 0;
    if (index == prefix.size())
        return curr->len;
    int c = prefix[index] - 'a';
    return startsWith(prefix, index+1, curr->next[c]);
}

int Trie::startsWith(string prefix){
    return startsWith(prefix, 0, head);
}

int main(){

    return 0;
}