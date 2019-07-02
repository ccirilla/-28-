#include <cmath>
#include <iostream>
#include <memory>
using namespace std;

class Figure
{
public:
    virtual
        void display() const = 0;

    virtual 
        double area() const = 0;

    virtual 
        ~Figure() { }
};

class Rectangle
: public Figure
{
public:
    Rectangle(size_t length, size_t width)
        : _length(length)
          , _width(width)
    {}

    void display() const 
    {   cout << "rectangle";    }

    double area() const
    {   return _length * _width;    }

    ~Rectangle() {  cout << "~Rectangle()" << endl; }

private:
    size_t _length;
    size_t _width;

};

class Circle
: public Figure
{
public:
    Circle(double radius)
        : _radius(radius)
    {}

    void display() const
    {   cout << "circle";   }

    double area() const
    {   return 3.14159 * _radius * _radius; }

    ~Circle() { cout << "~Circle()" << endl;    }

private:
    double _radius;

};

class Triangle
: public Figure
{
public:
    Triangle(size_t a, size_t b, size_t c)
        : _a(a)
          , _b(b)
          , _c(c)
    {}

    void display() const
    {   cout << "triangle"; }

    double area() const
    {
        size_t p = (_a + _b + _c) / 2;
        return sqrt(p * (p - _a) * (p - _b) * (p - _c));

    }

    ~Triangle() {   cout << "~Triangle()" << endl;  }   

private:
    size_t _a;
    size_t _b;
    size_t _c;
};

void display(Figure * fig)
{
    fig->display();
    cout << " 's area is " << fig->area() << endl;
}


class Factor
{
public:
    virtual
    Figure * create()=0; 
    virtual ~Factor() = default;
};

class RectangleFactory
:public Factor
{
    Figure * create(){
        return new Rectangle(3,4);
    }
};

class CircleFactory
:public Factor
{
    Figure * create(){
        return new Circle(3);
    }
};

class TriangleFactory
:public Factor
{
    Figure * create(){
        return new Triangle(3,4,5);
    }
};



int main()
{
    unique_ptr<Factor> rectangleFactory(new RectangleFactory);
    unique_ptr<Figure> rectangle(rectangleFactory->create());
    
    unique_ptr<Factor> circleFactory(new CircleFactory);
    unique_ptr<Figure> circle(circleFactory->create());

    unique_ptr<Factor> triangleFactory(new TriangleFactory());
    unique_ptr<Figure> triangle(triangleFactory->create());

    display(rectangle.get());
    display(triangle.get());
    display(circle.get());
    return 0;
}

