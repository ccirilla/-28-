#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
    Noncopyable(const Noncopyable &rhs) = delete;
    Noncopyable & operator = (const Noncopyable &) = delete;
};

}
#endif
