/*
You are given an array of strings tokens representing an expression in Reverse Polish Notation (RPN).
You must evaluate the expression and return the result.
Rules:
Each token is either:
An integer (can be negative)
One of the operators: +, -, *, /, %, ^ (power)
Division / should truncate toward zero.
Modulo % follows C++ style, result has the same sign as the dividend.
Power operator ^ represents exponentiation (a ^ b = a raised to the power of b).
The expression is valid, but can be very large (up to 10⁵ tokens). You must process in O(n).
Example 1:
Input: tokens = ["2", "3", "^", "4", "+", "5", "*"]
Explanation:
Step 1: 2 3 ^ → 2^3 = 8
Step 2: 8 4 + → 12
Step 3: 12 5 * → 60
Output: 60
Example 2:
Input: tokens = ["4", "13", "5", "/", "+"]
Explanation:
Step 1: 13 5 / → 2
Step 2: 4 2 + → 6
Output: 6
*/

#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

int rpn(vector<string> arr){

    stack<int> stack_;

    for(string s : arr){
        if(s == "+"){
            int b = stack_.top();
            stack_.pop();
            int a = stack_.top();
            stack_.pop();
            stack_.push(a+b);
        }
        else if(s == "-"){
            int b = stack_.top();
            stack_.pop();
            int a = stack_.top();
            stack_.pop();
            stack_.push(a-b);
        }
        else if(s == "*"){
            int b = stack_.top();
            stack_.pop();
            int a = stack_.top();
            stack_.pop();
            stack_.push(a*b);
        }
        else if(s == "/"){
            int b = stack_.top();
            stack_.pop();
            int a = stack_.top();
            stack_.pop();
            stack_.push(a/b);
        }
        else if(s == "%"){
            int b = stack_.top();
            stack_.pop();
            int a = stack_.top();
            stack_.pop();
            stack_.push(a%b);
        }
        else if(s == "^"){
            int b = stack_.top();
            stack_.pop();
            int a = stack_.top();
            stack_.pop();
            stack_.push(pow(a,b));
        }
        else{
            stack_.push(stoi(s));
        }
    }
    return stack_.top();
}

int main(){

    cout << rpn({"2", "3", "^", "4", "+", "5", "*"}) << endl;
    cout << rpn({"4", "13", "5", "/", "+"}) << endl;

    return 0;
}