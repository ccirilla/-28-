#include <stdlib.h>
#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
using namespace std;

class Observer;

class Subject
{
public:
    virtual
        void attach(Observer*obj) = 0;
    virtual
        void detach(Observer*obj) = 0;
    virtual 
        void notify() = 0;
    virtual ~Subject() {}
};

class Observer
{
public:
    Observer(const string &name)
        :_name(name)
    {}
    string name(){
        return _name;
    }
    virtual 
        void update()=0;
    virtual ~Observer() {}
private:
    string _name;
};

class Ring
: public Subject
{
public:
    void attach(Observer *ob) 
    {
        auto it = find(_oblist.begin(), _oblist.end(), ob);
        if(it == _oblist.end())
            _oblist.push_back(ob);
    }

    void detach(Observer * ob)
    {
        auto it = find(_oblist.begin(), _oblist.end(), ob);
        if(it != _oblist.end())
            _oblist.erase(it);
    }

    void alarm()
    {
        notify();
    }

    void notify() 
    {
        for(auto & ob : _oblist) {
            ob->update();

        }
    }
private:
    list<Observer*> _oblist;
};

class Baby
: public Observer
{
public:
    Baby(const string &name)
    :Observer(name)
    {}
    void update() {
        ::srand(::clock());
        int random = ::rand() % 100;
        if(random < 70) {
            cout << ">> Baby "<< name() << " started crying!" << endl;

        } else {
            cout << ">> Baby " << name() << " sleeps sweetly!" << endl;
        }
    }
};

class Nurse
: public Observer
{
public:
    Nurse(const string & name)
    :Observer(name)
    {}
    void update() 
    {
        ::srand(::clock());
        int random = ::rand() % 100;
        if(random < 70) {
            cout << ">> Nurse " << name() << " is ready to open the door!" << endl;

        } else {
            cout << ">> Nurse " << name() << " sleeps sweetly!" << endl;
        }
    }
};

class Guest
{
public:
    Guest(const string & name)
        : _name(name)
    {}
    void konck(Ring & ring)
    {
        cout << "Guest " << _name << " knock at the door！" << endl;
        ring.alarm();

    }
private:
    string _name;
};



int main()
{
    Ring ring;
    unique_ptr<Observer> baby1(new Baby("豆豆"));
    unique_ptr<Observer> baby2(new Baby("狗蛋"));
    unique_ptr<Observer> nurse1(new Nurse("如花"));
    unique_ptr<Observer> nurse2(new Nurse("翠花"));

    ring.attach(baby1.get());
    ring.attach(baby2.get());
    ring.attach(nurse1.get());
    ring.attach(nurse2.get());

    Guest guest("大鹏");
    guest.konck(ring);

    cout << ">> nurse " << nurse1->name() << " has left the room." << endl;
    ring.detach(nurse1.get());
    guest.konck(ring);
    return 0;
}

