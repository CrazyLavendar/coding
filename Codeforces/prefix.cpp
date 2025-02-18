#include <iostream>
using namespace std;

void Solution(string A, string B, int m, int n){
    int x = 0;
    for(int i = 0 ; i < n ;i++){
        if(A[x] == B[i]){
            x++;
        }
    }

    cout << x<< endl;
}


int main(){
    int t;
    cin >> t;
    while (t-- > 0){
    int digitA, digitB;
    cin >> digitA;
    cin >> digitB;

    string A, B;
    cin >> A;
    cin >> B;
    Solution(A, B, digitA, digitB);
    }

    return 0;
}