#include<iostream>
#include<vector>
#include<thread>
using namespace std;
typedef unsigned long long ULL;
int m = 1000, n =1000;
vector<vector<ULL> > A,B,C;


void fillArray(vector<vector<ULL> >& v){
    for(int i = 0; i < m ; i++){
        vector<ULL> temp;
        for(int j = 0; j < n ; j++){
            temp.push_back(i*j);
        }
        v.push_back(temp);
    }
}

void print(vector<vector<ULL> >& v){
    for(int i = 0; i < m ; i++){
        for(int j = 0; j < n ; j++){
            cout << v[i][j] << " " ;
        }
        cout << endl;
    }
}

void helper(vector<vector<ULL> >& A, vector<vector<ULL> >& B, vector<vector<ULL> >& C, int i){

            for(int j = 0; j < n ; j++){
                for(int k = 0; k < n ; k++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }

}

void multiply(vector<vector<ULL> >& A, vector<vector<ULL> >& B, vector<vector<ULL> >& C){
        for(int i = 0; i < m ; i++){
            vector<ULL> row(n);
            C.push_back(row);  
        }
    thread threads[m];
    for(ULL i = 0 ; i < m; i++){
        threads[i] = thread(helper, A, B ,C , i);
    }
    for(ULL i = 0 ; i < m; i++){
        threads[i].join();
    }
}

int main(){

    fillArray(A);
    fillArray(B);
    print(A);
    print(B);
    multiply(A,B,C);
    print(C);

    return 0;
}