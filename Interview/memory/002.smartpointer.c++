#include<iostream>
// using namespace std;

// template<class T> class SmartPointer{
//     public:
//     T* ptr;

//     explicit SmartPointer(T* p = NULL){
//         ptr = p;
//     }

//     T* operator->() { return *ptr; }
//     T operator=(&obj) { return ptr=obj; }
//     T& operator*(){
//         return &ptr;
//     }

//     ~SmartPointer(){
//         cout << "delete " << endl;
//         delete(ptr);
//     }


// };


// int main(){
//     SmartPointer<int>* s = new SmartPointer<int>();
//     *s = 20;

//     return 0;
// }

using namespace std;
 
// A generic smart pointer class
template <class T> class SmartPtr {
    T* ptr; // Actual pointer
public:
    // Constructor
    explicit SmartPtr(T* p = NULL) { ptr = p; }
 
    // Destructor
    ~SmartPtr() { delete (ptr); }
 
    // Overloading dereferencing operator
    T& operator*() { return *ptr; }
 
    // Overloading arrow operator so that
    // members of T can be accessed
    // like a pointer (useful if T represents
    // a class or struct or union type)
    T* operator->() { return ptr; }
};
 
int main()
{
    SmartPtr<int> ptr(new int());
    *ptr = 20;
    cout << *ptr;
    return 0;
}