
#include<iostream>
#include<thread>
#include<chrono>
using namespace std; 

typedef unsigned long long ULL;

int  N = 1000;

void mul(ULL **A, ULL **B, ULL **C){
    C[N] = (ULL *)malloc (N * sizeof(ULL));
    for(ULL i = 0 ; i < N ; i++){ // Ath row
        C[i] = (ULL *)malloc (N * sizeof(ULL));
        for(ULL j = 0 ; j < N ; j++){ // Bth col
            C[i][j] = 0;
            for(ULL k = 0; k < N ; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void threadMulHelper(ULL **A, ULL **B, ULL **C, ULL i){
        for(ULL j = 0 ; j < N ; j++){ // Bth col
            for(ULL k = 0; k < N ; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
}

void threadMul(ULL **A, ULL **B, ULL **C){
    C[N] = (ULL *)malloc (N * sizeof(ULL));
        for(ULL i = 0 ; i < N ; i++)
            C[i] = (ULL *)malloc (N * sizeof(ULL));
    thread threads[N];
    for(ULL i = 0 ; i < N; i++){
        threads[i] = thread(threadMulHelper, A, B ,C , i);
    }
    for(ULL i = 0 ; i < N; i++){
        threads[i].join();
    }
}

void printArr(ULL **arr, ULL M , ULL N){
    for(ULL i = 0 ; i < M; i++){
        for(ULL j =0 ; j < N; j++){
            cout << arr[i][j] << " " ;
        }
        cout << endl;
    }
}
void fillArr(ULL **arr, ULL M , ULL N){
    arr[N] = (ULL *)malloc(M * sizeof(ULL)) ;
    for(ULL i = 0 ; i < M; i++){
        arr[i] = (ULL *)malloc(N * sizeof(ULL));
        for(ULL j =0 ; j < N; j++){
            arr[i][j] = (i+1)*(j+1);
        }
    }
}

int main(){
    ULL *A[N], *B[N] , *C[N];
    fillArr(A,N,N);
    // printArr(A,N,N);
    fillArr(B,N,N);
    // printArr(B,N,N);
    auto start = chrono::system_clock::now();
    mul(A,B,C);
    printArr(C,N,N);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "normal mul took : " << duration.count() << " milliseconds"  << endl;
    start = chrono::system_clock::now();
    threadMul(A,B,C);
    printArr(C,N,N);
    end = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "thread mul took : " << duration.count() << " milliseconds"  << endl;
    return 0;
}