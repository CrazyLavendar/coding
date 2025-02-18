#include<iostream>
#include<memory>
#include<string>
#include<vector>

using namespace std;

class Animal{
public:
    // string name;
    // Animal(string name):name(name){}
    Animal(){}
    virtual void voice() = 0;
    ~Animal(){}
};

class Dog : public Animal{
public:
    string name;
    Dog(string name):name(name){
        cout << "dog " << name << " created"  << endl;
    }
    void voice() override{
        cout << " Woow " << endl;
    }
    ~Dog(){
        cout << "dog " << name << " deleted"  << endl;
    }
};

class Cat : public Animal{
public:
    string name;
    Cat(string name):name(name){
        cout << "cat " << name << " created"  << endl;
    }
    void voice() override{
        cout << " Meow " << endl;
    }
    ~Cat(){
        cout << "Cat " << name << " deleted"  << endl;
    }
};

int main(){

    unique_ptr<Dog> d1{new Dog{"juju"}};
    unique_ptr<Dog> d2 = make_unique<Dog>("bobo");
    unique_ptr<Cat> c1 = make_unique<Cat>("mumu");
    vector<unique_ptr<Animal>> animals;

    animals.push_back(move(d2));
    // Animal* dog1 = new Dog("dog1");
    // // animals.push_back(new Dog());

    //clear(animals);

    return 0;
}