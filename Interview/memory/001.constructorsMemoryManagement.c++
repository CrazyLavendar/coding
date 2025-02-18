#include<iostream>
using namespace std;

struct Student{
    public:
    int roll;
    string teacher;
    Student(){}
    Student(Student& obj){
        roll = obj.roll;
        teacher = obj.teacher;
        cout << " copy call from Student" << endl;
    }
};

class School{
    public:
    Student *student;

    School(int r = 000, string s = "xxx"){
        student = new Student();
        student->roll = r;
        student->teacher = s;
        cout << " constructor call " << endl;
    }

    School(School& obj){
        student = new Student();
        student = obj.student;
        cout << " copy call " << endl;
    }

    ~School(){
        cout << " destrucor call " << endl;
        delete student;
    }
};
int main(){
    
    School s1;

    if(true){
        School s2 = s1;
    }

    return 0;
}