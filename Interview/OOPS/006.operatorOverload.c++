#include<iostream>
using namespace std;
class Point{
public:
    int x,y;
    Point () : x{0}, y{0} {}
    Point (int x , int y) : x{x} , y {y}{}
    Point operator + ( Point p2){
        Point p;
        p.x = x+ p2.x;
        p.y = y+ p2.y; 
        return p;
    }
};

int main(){
    cout << "operator overload" << endl; 
    Point a(1,2), b (10,4);
    Point c = a + b;

    cout << c.x << " " << c.y << endl;
    return 0;
}