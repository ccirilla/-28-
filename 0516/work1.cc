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
    ~Student()
    {
        delete []_name;
        cout << "Destory !" << endl;
    }
    void print()
    {
        cout << "name : " << _name <<endl;
        cout << "id : " << _id <<endl;
    }

private:
    void * operator new (size_t sz)
    {
        void * ret = calloc(1,sz);
        return ret;
    }
    void operator delete (void * ret)
    {
        free(ret);
    }

private:
    char * _name = nullptr;
    int _id = 0;
};




int main()
{
    Student s1("Jinx",1001);
    s1.print();
    //Student * ps = new Student("Ashe",1002);
    return 0;
}

