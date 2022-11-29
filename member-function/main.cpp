#include <iostream>
using namespace std;

class Cat
{
public:
    void fun1() { cout << "Not const member function" << endl; }
    void fun2() const { cout << "const member function" << endl; }
    //常成员函数 不能调用 普通成员函数
    void fun3() const 
    {
        // fun1();//error
    }
};

int main()
{
    Cat cat;
    cat.fun1();
    cat.fun2();

    //1.常对象
    const Cat c1;
    // c1.fun1();   //error
    c1.fun2();
    //2.常引用
    const Cat& rc = c1;
    // rc.fun1();   //error
    rc.fun2();
    //3.常指针
    const Cat* pc = new Cat;
    // pc->fun1();  //error
    pc->fun2();
    
    return 0;
}