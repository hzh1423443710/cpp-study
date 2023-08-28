#include <iostream>

#define ENABLE_EXPLICIT 0
// explicit

class Base
{
public:
#if ENABLE_EXPLICIT
    // 1.隐式类型构造
    explicit Base(int n) {}
    // 2.类型转换函数
    explicit operator int() const
    {
        return 10;
    }
#else
    // 1.隐式类型构造
    Base(int n) {}
    // 2.类型转换函数
    operator int() const
    {
        return 10;
    }
#endif   
};

void test()
{
#if ENABLE_EXPLICIT
    // 1.隐式类型转换 error
    Base b = 10;
    // 2.类型转换函数 error
    int n = static_cast<int>(b);
    int n2 = (int)b;
#else
  // 1.隐式类型转换 correct
    Base b = 10;
    // 2.类型转换函数 correct
    int n = static_cast<int>(b);
    int n2 = (int)b;
#endif
}

int main()
{
    test();
    return 0;
}