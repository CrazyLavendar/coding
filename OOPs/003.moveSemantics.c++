#include<iostream>

using namespace std;

class MoveSemantic{

public:
    MoveSemantic(int data) : data{data}{}
    MoveSemantic(MoveSemantic&& other) : data{other.data}{
        cout << " Semantic" << endl;
        other.data = 0;
    }

    MoveSemantic(MoveSemantic& other){
        cout << "copy " << endl;
        data = (other.data);
    }

    // MoveSemantic operator = (MoveSemantic& other){
    //     MoveSemantic ms(other.data);
    //     // data = other.data;
    //     other.data = 0;
    //     return ms;
    // }
    int data;
};

int main(){
    MoveSemantic ms(100);
    MoveSemantic ms2 = std::move(ms);
    MoveSemantic ms3 = ms2;
    cout << ms.data << endl;
    cout << ms2.data << endl;

    return 0;
}