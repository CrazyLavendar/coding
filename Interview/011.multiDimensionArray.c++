#include <iostream>
#include<vector>
using namespace std;
int M = 4, N = 5;
// Driver Code

void printArr(int** pArr){
    for(int i = 0 ; i< M; i++){
        for(int j = 0; j <N ; j++){
            cout << pArr[i][j] << " " ;
        }
         cout << endl;
    }
}



int main()
{

    // Pointer Array
    int count = 0;
    int *pArr[M]; // = new int*[M];
    for(int i = 0 ; i < M ; i++)
        pArr[i] = new int[N];

    for(int i = 0 ; i< M; i++){
        for(int j = 0; j <N ; j++){
            pArr[i][j] = count++;
        }
    }

    for(int i = 0 ; i< M; i++){
        for(int j = 0; j <N ; j++){
            cout << pArr[i][j] << " " ;
        }
         cout << endl;
    }

    printArr(pArr);

    // delete[] pArr;
    count = 0;

    // vector<vector<int>> v(pArr, pArr + M * N);
    vector<vector<int>> v;
    for(int i = 0; i <  M ; i ++){
        vector<int> temp;
        for(int j = 0 ; j < N ; j++){
            temp.push_back(count++);
        }
        v.push_back(temp);
    }

    for(int i = 0 ; i< M; i++){
        for(int j = 0; j <N ; j++){
            cout << v[i][j] << " " ;
        }
         cout << endl;
    }


    int arr[M][N];

    count = 0;

    for(int i = 0 ; i< M; i++){
        for(int j = 0; j <N ; j++){
            arr[i][j] = count++;
        }
    }

    for(int i = 0 ; i< M; i++){
        for(int j = 0; j <N ; j++){
            cout << arr[i][j] << " " ;
        }
         cout << endl;
    }

    printArr(arr);
 
    return 0;
}