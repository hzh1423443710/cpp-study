#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class A
{
public:
    A(int num = 10) : m_num(num) { cout << "A construct function" << endl; }
    int m_num;
};
class B
{
public:
    B(int num = 10) : m_num(num) { cout << "B construct function" << endl; }
    int m_num;
};
class C
{
public:
    C(int num = 10) : m_num(num) { cout << "C construct function" << endl; }
    int m_num;
};

class Combine
{
public:
    //初始化列表的顺序只与类中成员变量的声明顺序有关
    Combine(int a1 = 1, int a2 = 2, int a3 = 3) : c(a3), b(a2), a(a1) {}
    A a;
    B b;
    C c;
};

class People
{
public:
    People(const string &name) : m_name(name), m_len(m_name.size()) {} // error 也可以更改成员的声明顺序 也可以m_len(name.size())
    People(const char *name) : m_name(name == NULL ? "" : name), m_len(name == NULL ? 0 : strlen(name)) {}

    int m_len;     //先初始化
    string m_name; //后初始化
};

void test1();
void test2()
{
    People peo("Frank");
    cout << peo.m_name << "," << peo.m_len << endl;
    People peo2(string{"hello world"});
    cout << peo2.m_name << "," << peo2.m_len << endl;
}

int main()
{
    test2();

    return 0;
}

void test1()
{
    Combine cc;
    cout << cc.a.m_num << " " << cc.b.m_num << " " << cc.c.m_num << endl;
    Combine cc2(30, 20, 10);
    cout << cc2.a.m_num << " " << cc2.b.m_num << " " << cc2.c.m_num << endl;
}