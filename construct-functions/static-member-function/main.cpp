#include <iostream>
using namespace std;

class Cat
{
public:
    Cat(int age) : m_age(age) {}
    static void fun() //const //静态成员函数没有const限定
    {
        //this->m_id = 1002;//error this值适用于非静态成员函数
        //m_age++;          //error 无this指针
        m_id++;             //只能操作静态成员
    }
    ~Cat() {}

public:
    int m_age;
    static int m_id;    //类内声明
};
int Cat::m_id = 1001;   //类外定义并初始化

int main()
{
    Cat c(10);
    cout << c.m_age << " " << c.m_id << endl;   //通过对象访问
    cout << Cat::m_id << endl;                  //通过类名访问
    Cat::fun();                                 //通过类名访问
    cout << Cat::m_id << endl;

    return 0;
}
