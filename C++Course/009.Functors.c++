#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// Fucnctor
class Compare{
public:
    template<typename T> 
    bool operator()(T a, T b){
        return a > b;
    }
};

class Complex{

public:
    int val;
    int img;

    Complex () {
        val = 0;
        img = 0;
    }

    Complex (int a, int b){
        val = a;
        img = b;
    }

    // functoe
    Complex operator + (Complex& b){
        Complex c;
        c.val = val + b.val;
        c.img = img + b.img;
        return c;
    }
    

};

int main(){
    vector<int> arr = {3,4,5,6,1,2,-1,6};
    // sort(arr.begin(), arr.end(), Compare());

    // lambda
    sort(arr.begin(), arr.end(),
     [](int a, int b){
        return a > b;}
    );


    // for(int& a : arr){
    //     cout << a << " ";
    // }

    Complex a(1,2), b(4,5);
    Complex c = a + b;

    cout << c.val << " " << c.img << endl;
    return 0;
}