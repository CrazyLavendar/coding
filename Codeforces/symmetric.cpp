#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

void solution(int n, string s){
    set<char> ss;
    string u = "";
    for(int i = 0; i < n ; i++){
        char c = s[i];
        if(ss.count(c) == 0){
            ss.insert(c);
            u = u + c;
        }
    }

    int m = u.size();
    unordered_map<char, char> mp;

    sort(u.begin(),u.end());

    for(int i = 0 ; i < m ; i++){
        mp[u[i]] = u[m-i-1];
    }

    string res = "";
    for(int i = 0; i < n ; i++){
        char c = s[i];
        res += mp[c];
    }
    cout << res << endl;

}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        string s;
        cin >> n;
        cin >> s;
        solution(n,s);
    }
    return 0;
}