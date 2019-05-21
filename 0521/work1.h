//实现PIMPL设计模式模式


class Line
{
public:
    Line(int,int ,int ,int);
    ~Line();
    void printLine() const;
    class LineImpl;
private:
    LineImpl * _pimpl;
};

