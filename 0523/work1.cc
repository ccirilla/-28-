#include <iostream>
using std::cout;
using std::endl;

const double pai = 3.1415926;
class Circle
{
public:
    Circle() = default;
    Circle(double r):_r(r) {}
    double getArea(){  return pai * _r *_r;  }     //获取圆的面积            
    double getPerimeter() {  return pai * 2 *_r;  }//获取圆的周长              
    void  show(){
        cout << "r = " << _r << endl;
        cout << "l = " << getPerimeter() << endl;
        cout << "s = " << getArea() << endl;

    }       //将圆的半径、周长、面积输出到屏幕
private:
    double _r = 0;
};

class Cylinder
:public Circle
{
public:
    Cylinder() = default;
    Cylinder(double r, double h)
    : Circle(r)
    , _h(h)
    {}
    double getVolume() {  return getArea() * _h;  }
    void  showVolume() {  cout << "v = " << getVolume() << endl; } 
private:
    double _h = 0;
};


int main()
{
    Cylinder c(6.66,8.88);
    c.show();
    c.showVolume();
    return 0;
}

