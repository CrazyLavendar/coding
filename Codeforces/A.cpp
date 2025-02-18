#include<iostream>    
#include <vector> 
#include<algorithm>

using namespace std;

int solve(int x, int max){
    int curr = 0;
    int i = 1;
    while((i*x) <= max){
        curr += ((i++) * x);
    }
    return curr;
}
int main(){
    int t;
    cin >> t;
    while (t--)
    {
        int max;
        cin >> max;

        int res = -1, res_max = 0;
        for(int i = 2; i<= max; i++){

            int temp = solve(i,max);
            //cout << i << " " << temp << endl;
            if(res_max  < temp){
                res = i;
                res_max = temp;
            }
        }

        cout << res << endl;

    }
     


    return 0;
}