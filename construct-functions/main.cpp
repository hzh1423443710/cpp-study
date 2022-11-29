#include <iostream>
using namespace std;

class A
{
public:
    A(int num) : m_a(num)
    {
        cout << "A Have parameter construct funciton" << endl;
    }
    A(void)
    {
        cout << "A No parameter construct function" << endl;
        m_a = 0;
    }
    A(const A& a)
    {
        cout << "A copy construct function" << endl;
        m_a = a.m_a;
    }
    A(A&& a)
    {
        cout << "A right reference costruct function" << endl;
        m_a = a.m_a;
    }
public:
    A& operator= (A&& a)
    {
        cout << "A right reference assignment function" << endl;
        this->m_a = a.m_a;
        return *this;
    }
    A& operator= (const A& a)
    {
        cout << "A const reference assignment function" << endl;
        this->m_a = a.m_a;
        return *this;
    }
public:
    int m_a;
};

class B
{
public:
    A a;
};

A fun1()
{
    A* pa = new A(10);
    return *pa;
}

A fun2()
{
    A a(10);
    cout << "In fun2 &a = " << &a << endl;
    return a;
}

void test1();
void test2();
void test3();

int main()
{
    test3();

    return 0;
}

void test1()
{
    A a;
    cout << a.m_a << endl;
    
    cout << "-------------" << endl;

    A a2(10);
    cout << a2.m_a << endl;

    cout << "-------------" << endl;

    A a3;
    a3 = 100;
    cout << "-------------" << endl;
    a3 = A{100};
    cout << "-------------" << endl;
    a3 = a;
}

void test2()
{
    B b;
    cout << "----------" << endl;
    B b2(b);
    cout << "----------" << endl;
    B b3;
    b3 = b;
}

void test3()
{
    A obj = fun1();
    cout << "obj.m_a = " << obj.m_a << endl;
    cout << "------" << endl;

    A obj2 = fun2();
    cout << "obj2.m_a = " << obj2.m_a << ", &obj2 = " << &obj2 << endl;
    cout << "------" << endl;
}