#include<iostream>    
#include <vector> 
#include <cmath>

using namespace std;
int main(){
    int t;
    cin >> t ;
    while (t--)
    {
        long long n;
        cin >> n;

        long long res  = 0;
        
        while(n > 0){
            res += n;
            n /= 2;
        }
        
        cout << res << endl;
    }
     


    return 0;
}