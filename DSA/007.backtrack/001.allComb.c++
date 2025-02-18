#include<iostream>
#include<string>
// #include<bits/stdc++.h>

using namespace std;

void backtrack(char *str, string curr, int index,  int end, vector<string>& v){

    v.push_back(curr);

    cout << index << " " << end << endl;
    for(int i = index ; i < end ; i++){
    
        curr += str[i];
        cout << " curr : " << curr << endl;
        backtrack(str, curr ,i+1,end, v);
        curr.erase(curr.size() - 1);

    }

}

void bitmap(char *str, int n, vector<string>& v){

    int e = pow(2,n);
    cout << e << endl;
    for(int i  =0 ; i < pow(2,n) ; i++){
        string temp = "";
        int x  = 1; //setbit
        int place = 0;
        while(x <= i){
            
            if(x & i){
                
                temp += str[place] ;
            }
            place++;
            x <<= 1;
        }
        cout << i << " " << temp << endl;
        v.push_back(temp);
    }


}

int main(){

    char str[] = {"vimal"};

    vector<string> res; 
    // backtrack(str, "", 0 , 5, res);

    bitmap(str , sizeof(str)/sizeof(char) - 1 , res);

    int c = 0;
    // for(string s : res){
    // cout << c++ << "  "  << s << endl;
    // }


    return 0;
}