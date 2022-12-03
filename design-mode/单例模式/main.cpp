#include <iostream>
#include <string>
using namespace std;

//饿汉式
class Singleton
{
public:
    //通过静态成员函数 访问 唯一对象
    static Singleton &getInstance()
    {
        return m_instance;
    }
    const string &getName() const
    {
        return m_name;
    }

private:
    //私有化构造函数->类外不能创建对象
    explicit Singleton(const string &name) : m_name(name) { cout << "construct function " << m_name << endl; }
    Singleton(const Singleton &other) = delete;
    Singleton &operator=(const Singleton &other) = delete;

private:
    static Singleton m_instance; //唯一的实例对象
    string m_name;
};
Singleton Singleton::m_instance{string("cactus")}; //唯一的静态对象初始化

int main()
{
    cout << "---------->the program starts" << endl;//程序开始之前对象就已经创建了
    //×
    // Singleton obj;
    // Singleton* pboj = new Singleton;

    //√
    Singleton &obj1 = Singleton::getInstance();
    Singleton &obj2 = Singleton::getInstance();
    Singleton &obj3 = Singleton::getInstance();
    cout << "&obj1 = " << &obj1 << " obj1.m_name: " << obj1.getName() << endl;
    cout << "&obj2 = " << &obj2 << " obj2.m_name: " << obj2.getName() << endl;
    cout << "&obj3 = " << &obj3 << " obj3.m_name: " << obj3.getName() << endl;

    return 0;
}