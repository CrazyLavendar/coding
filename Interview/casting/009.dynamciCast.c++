#include <iostream>
 
using namespace std;

// Base Class declaration
class Base {
public:
     void print()
    {
        cout << "Base" << endl;
    }
};
 
// Derived1 class declaration
class Derived1 : public Base {
public:
    void print()
    {
        cout << "Derived1" << endl;
    }
};
 
// Derived2 class declaration
class Derived2 : public Base {
public:
    void print()
    {
        cout << "Derived2" << endl;
    }
};
 
// Driver Code
int main()
{
    Derived1 *d1;
 
    // Base class pointer holding
    // Derived1 Class object
    Base* bp = dynamic_cast<Base*>(d1);
 
    // // Dynamic_casting
    Derived2* d2 = dynamic_cast<Derived2*>(d1);
    // if (dp2 == nullptr)
    //     cout << "null" << endl;
    // else
    //     cout << "not null" << endl;

    
    bp->print();
    d1->print();
    d2->print();
 
    return 0;
}