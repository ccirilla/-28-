#include <string>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
class Person
{
public:
    Person(const string &name,const int age)
    : _name(name)
    , _age(age)
    {}
    virtual void display() const
    {
        cout << "name : " << _name << endl;
        cout << "   age : " << _age << endl;
    }
private:
    string _name;
    int _age;
};

class Employee
:public Person
{
public:
    Employee(const string &name,const int age,const string department,const double salary)
    : Person(name,age)
    , _department(department)
    , _salary(salary)
    {
        ++num;
        sum += _salary;
    }
    void display() const override
    {
        Person::display();
        cout << "   department : " << _department << endl;
        cout << "   salary : " << _salary  << endl;
    }
    static double getAvgSalary() {  return sum/num ;  }
private:
    string _department;
    double _salary;
    static double sum;
    static int num ;
};

double Employee::sum = 0;
int  Employee::num = 0;

void print( std::vector<Employee> &e)
{
    for(Person &tmp:e)
    {
        tmp.display();
    }
    cout << "AVGsalary : " << Employee::getAvgSalary() << endl;
}


int main()
{
    std::vector<Employee> e;
    e.emplace_back("Theshy",28,"IG",8888.88);
    e.emplace_back("Uzi",23,"RNG",6666.66);
    e.emplace_back("Faker",26,"SKT T1",9999.99);
    print(e);
    return 0;
}

