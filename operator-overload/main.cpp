#include <iostream>
using namespace std;

class Cat
{
    friend ostream &operator<<(ostream &output, const Cat &o)
    {
        output << "m_num = " << o.m_num;
        return output;
    }

private:
    int m_num;

public:
    Cat(int num) : m_num(num) {}
    ~Cat() {}

public:
    /*
     *  第一个const:1.支持链式 2.不允许这种操作:(c1+c2) = c3; 
     *  第二个const:接受左值引用,常引用,右值引用
     *  第三个const:可供常对象使用
     *
     */
    const Cat operator+(const Cat &other) const
    {
        Cat temp(m_num + other.m_num);
        return temp;
    }
    /* 右值引用
    const Cat operator+(Cat &&other) const
    {
        Cat temp(m_num + other.m_num);
        return temp;
    }
    */
};


int main()
{
    cout << "&cout:: " << &std::cout << endl;
    Cat c0(1000);
    const Cat c1(1001);
    Cat c2(1002);
    const Cat c3(1003);

    c2 = c1 + c0;        //参2:左值引用
    c2 = c2 + c1;        //参2:常引用
    c2 = c2 + Cat(1001); //参2:右值引用
    c2 = c1 + c3;        //参1:常对象
    cout << c2 << endl;

    return 0;
}