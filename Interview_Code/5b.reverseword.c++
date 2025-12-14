/*

Given a sentence s, perform the following operations in this order:
Reverse characters inside each word
Reverse the order of words
Remove extra spaces (leading, trailing, and multiple spaces)
Example:
Input:
"  hello   world  from   chat gpt "

Step 1: "olleh   dlrow  morf   tpg tahc"
Step 2: "tpg tahc morf dlrow olleh"

Final Output:
"tpg tahc morf dlrow olleh"
*/
#include<iostream>
#include<stack>
#include<string>
#include<vector>

using namespace std;

string twoPointerApproach(string s){
    
}

string reverseString(string s){
    int i = 0;
    stack<string> stack_;
    while(s[i] == ' '){
        i++;
    }
    bool break_ = false;
    string curr = "";
    for(; i < s.size(); i++){
        char c = s[i];
        if (break_ && c == ' ')
            continue;
        else if (c == ' '){
            break_ = true;
            stack_.push(curr);
            curr = "";
        }
        else{
            break_ = false;
            curr = c + curr;
        }
        // cout << curr << endl;
    }
    if(curr.size() > 0)
        stack_.push(curr);
    string res = "";
    while(!stack_.empty()){
        res += stack_.top() + " ";
        stack_.pop();
    }
    int n = res.size();
    if(res[n - 1] == ' ')
    {
        res = res.substr(0, n-1);
    }
    return res;

}

int main(){
    string s = " Swetha  loves vimal     So      much";
    cout << reverseString(s) << endl;
    s = "AI   will  change   the   world";
    cout << reverseString(s) << endl;
    return 0;
}