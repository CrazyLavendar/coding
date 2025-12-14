#include<iostream>
#include<memory>

using namespace std;

class B;

class A{
public:
  ~A(){
    cout << "destroyed A" << endl;
  }
  public:
  shared_ptr<B> b_ptr;
};

class B{
public:

  ~B(){
    cout << "destroyed B" << endl;
  }

  shared_ptr<A> a_ptr; //// ---> need to be weak_ptr, else circular dependency
};

int main(){
    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;
    return 0;
}