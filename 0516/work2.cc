#include <iostream>
#include <string.h>
using std::cout;
using std::endl;



class Student
{
public:
    Student(const char * name,int id)
    :_name(new char[strlen(name)+1])
    ,_id(id)
    {
        strcpy(_name,name);
        cout << "Constuct !" << endl;
    }
    Student() = default;
    void print()
    {
        cout << "name : " << _name <<endl;
        cout << "id : " << _id <<endl;
    }
    void destory()
    {
        delete this;
    }

private:
    ~Student()
    {
        delete []_name;
        cout << "Destory !" << endl;
    }

private:
    char * _name = nullptr;
    int _id = 0;
};




int main()
{
    //Student s1("Jinx",1001);
    Student * ps = new Student("Ashe",1002);
    ps->print();
    ps->destory();
    return 0;
}

