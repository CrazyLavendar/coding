/*
Consider the following C++ code:

#include <iostream>
using namespace std;

class Base {
public:
    virtual void f1() { cout << "Base::f1\n"; }
    virtual void f2() { cout << "Base::f2\n"; }
    int x;
};

class Derived : public Base {
public:
    void f1() override { cout << "Derived::f1\n"; }
    virtual void f3() { cout << "Derived::f3\n"; }
    int y;
};

int main() {
    Base* b = new Derived();
    b->f1();
    b->f2();
}


⸻

Tasks
	1.	Draw the memory layout of a Derived object, including:
	•	vptr location
	•	data members
	•	vtable contents
[ans]:
	Derived : public Base		Derived : VTable	Base
	__vptr1 = &f1()-------------> f1()------------>	f1()
	-vptr2
		
	y;												
	f1()								
	f3()

	2.	What does the vtable for Base look like?
	What about the vtable for Derived?

[Ans]
	Base : VTable
	f3()

	Derived : VTable
	f1()
	f2()


	3.	Which functions are called at runtime and why?
	•	b->f1()
	•	b->f2()
[Ans] : b->f1() calls Derived::f1() , since it is core logic of inheritance.
		b->f2() calls Based::f1(), No overridden function avaiable in vTable. 
	4.	What happens if f2() is made non-virtual in Base?
[ans]: There will no change in current output. There are no override function useds Base::f2(). vptr and vtable size will be reduced in Base object after f2() made non virtual.
	5.	How many vptrs exist in the Derived object? Why?
[ans]: Two. One is unassigned to Base::f1(), Other one unassigned , since it is not override in derived class.

⸻

Follow-ups interviewers love
	•	Where is the vptr stored (object or class)?
[ans]:	vptr is stored for each object individually.
	•	Is vtable layout standardized by C++?
[ans]: No. Though C++ mandates vtable layout, It depends on compilers for executing run time polymorphism..
	•	Can the compiler devirtualize these calls?
[ans]: Compiler can devirtualize. (i.e) avoid override.
	•	What changes with multiple inheritance?
[ans]: Derived object can have multiple Base classs to override.
Vptr and Vtable has to accomodate this.
	•	How does virtual inheritance affect layout?
[ans]: Allow to solve diamond problem inheritance and reduce vtable size.
For Ex: Base -> Derived1 -> Derived2, 
class Derived1 : virtual public Base{..}
class Derived2 : public Derived2{..}
Here only Derived2 created Vtable for Base and allow override
Derived2 is responsible for calling Base constructor.

⸻
*/