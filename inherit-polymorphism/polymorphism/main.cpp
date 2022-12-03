#include <iostream>
using namespace std;

class Base {
protected:
    virtual int fun() const {
        cout << "Base::fun" << "this" << this << endl;
        return 0;
    }
public:
    void normal() const{
        cout << "Base::normal " << "this:" << this << endl;
        fun();
    }

};

class Drived : public Base {
protected:
    int fun() const {
        cout << "Drived::fun" << " this: " << this << endl;
        return 1;
    }
public:
    /* error 返回值类型不同
    void fun() const {
        cout << "Drived::fun" << endl;
    }
    */
};

class A {

};
class B :public A {

};
class C :public A {

};

void test()
{
    Drived d;
    cout << "main::&d:" << &d << endl;
    d.normal(); //通过普通函数调用虚函数

    Base* pb = static_cast<Base*>(&d);
    pb->normal();
}

int main()
{
    B b;
    A* pa = &b;
    B* pb = static_cast<B*>(pa);    //合理
    C* pc = static_cast<C*>(pa);    //能转换但不合理
    //C* pc = dynamic_cast<C*>(pa);  //报错 dynamic_cast 可以检测不合理的转换

    return 0;
}