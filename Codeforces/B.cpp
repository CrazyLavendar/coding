#include<iostream>    
#include <vector> 
#include <cmath>

using namespace std;
int main(){
    int t;
    cin >> t ;
    while (t--)
    {


        vector<int> arr;
        int size;
        cin >> size;

        for(int i = 0 ; i< size; i++){
            int x; 
            cin >> x;
            arr.push_back(x);
        }

        long long sum = abs(arr[0]), op = 0;
        bool isPrevNeg = false;

        if(arr[0] < 0){
            isPrevNeg = true;
        }

        for(int i = 1 ; i < size ; i++){

            if(arr[i] == 0){
                continue;
            }
            
            if(isPrevNeg && arr[i] > 0)
            op++;

            if(arr[i] < 0){
                isPrevNeg = true;
            }else{
                isPrevNeg = false;
            }

            sum += abs(arr[i]);
        }

        if(isPrevNeg)
            op++;

        cout << sum <<  " " << + op << endl;
        arr.clear();
    }
     


    return 0;
}