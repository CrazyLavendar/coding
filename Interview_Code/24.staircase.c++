/*
[30/12/2025, 10:56:26 PM] Swetha Vimal: You are climbing a staircase with n steps.

Each time, you may climb either 1 step or 2 steps.

Return the number of distinct ways to reach the top.

Constraints
	•	1 ≤ n ≤ 10⁷
	•	Aim for O(n) time and O(1) space

Follow-ups
	•	How would you optimize space?
[Ans:] Used p and q variables to store (n-1) and (n-2) values. Storing overall array upto n is not necessary.
Implementeed O(1)
	•	Can this be solved in O(log n) time?
[Ans:] No. I couldn't get 
	•	How does the solution change if you can climb up to k steps at a time?
[Ans:] If the question is "climb up to k steps at a time" and min possible steps required, I will try to max k steps each time. 
Solution is "(k/n) +1"
If the question is "climb up to k steps at a time" and distict possible steps, I should try with factorials.

	•	What if some steps are broken and cannot be used?
[Ans:]
I try to experiment with n! divisble with x! , where x is steps not allowed

Example 
Input: n = 5
Output: 8

Explanation:
Ways = [1+1+1+1+1,
        1+1+1+2,
        1+1+2+1,
        1+2+1+1,
        2+1+1+1,
        2+2+1,
        2+1+2,
        1+2+2]

Rough:
1 - 1
2 - 11, 2
3 - 111,21,12
4 - 1111,211,121,112,22

*/

#include<iostream>

using namespace std;


int solution(int n){
    if (n <= 2)
        return n;
    int p = 1, q = 2;
    for(int i = 3; i <= n; i++){
        int temp = q;
        q = p + q;
        p = temp;
    }
    return q;
}

int main(){
    cout << solution(5) << endl;
    return 0;
}