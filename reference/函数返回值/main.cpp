#include <iostream>
using namespace std;

int fun()
{
    int num  = 100;
    cout  << "&num = " << &num << endl;
    return num;
}

int main()
{
    int a = fun();      //(1).num赋值给临时变量(2).num销毁(3).临时变量赋值给a
    cout << "a = " << a << endl;

    //int& rf = fun();    //× error 普通引用只能接受左值
    const int& rf = fun();//√ 
    cout << "&rf = " << &rf << " , rf = " << rf << endl;//地址不一样

    return 0;
}