// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

class Base{
  public:
  virtual void fun(){
      cout << " hello " << endl;
  }
  void print(){
      cout << "Base" << endl;
  }
};

class Child : public Base{
  public:
  void fun(){
      cout << "Hello world" << endl;
  }
  void print(){
      cout << "Child" << endl;
  }
};

int main() {
    // Write C++ code here
    Base* b = new Child();
    b->fun(); // Prints base class
    b->print(); // Prints child class

    return 0;
}