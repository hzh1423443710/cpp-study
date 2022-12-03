#include <iostream>
using namespace std;


class Cat
{
public:
    Cat():num(1) {}
    void fun() {
        cout << "Base::fun()" << endl;
    }
    int num;
};

class smallCat : public Cat
{
public:
    using Cat::fun; 
public:
    smallCat():num(100){}
    void fun(int) {
        cout << "Derived::fun()" << endl;
    }
    int num;
};

class Dog
{
private:
    /* data */
public:
    Dog(int){}
    Dog(){}
};

class A
{
private:
    int a;
public:
    A(/* args */) {cout << "A" << this << endl;}
    ~A() {}
};

class B
{
private:
    int score;
    int b;
public:
    B(/* args */) {cout << "B" << this << endl;}
    ~B() {}
};

class C
{
private:
    int c;
public:
    C(/* args */) {cout << "C" << this << endl;}
    ~C() {}
};

class D :public A,public B,public C
{
private:
    int d;
public:
    D(/* args */) {cout << "D" << this << endl;}
    ~D() {}
};

void mutiInhert()
{
    D o;
    A* pa = &o;
    B* pb = &o;
    C* pc = &o;

    cout << pa << endl;
    cout << pb << endl;
    cout << pc << endl;//地址偏移
}

int main()
{   


    return 0;
}