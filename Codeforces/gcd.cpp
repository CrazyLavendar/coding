#include<iostream>
#include<math.h>
using namespace std;

int gcd(int a, int b){
    if (a == 0)
        return b;
    return gcd(b % a, a);

}
void Solution(int num){
    int curr = 1, res = 1;
    for(int i = 1; i < num; i++){
        if (gcd(num, i) + i  > curr){
            curr = gcd(num, i) + i;
            res = i;
        }
    }
    cout << res << endl;
}


int main(){
    int testcases;
    cin >> testcases;
    for(int i = 0; i < testcases ; i++){
        int num;
        cin >> num;
        Solution(num);
    }
    return 0;
}