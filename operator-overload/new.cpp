#include <iostream>
#include <cstdlib>
using namespace std;

class Cat
{
private:
    int m_num;
public:
    Cat(int num):m_num(num) { cout << "construction function" << endl; }
    ~Cat() { cout << "destruction function" << endl; }
public:
    static void* operator new(size_t size)//static:先分配了内存,才构造出了对象
    {
        cout << "operator new" << endl;
        void* p = malloc(size);
        return p;
    }
    static void operator delete(void* p)//static:对象销毁了就不能free了
    {
        cout << "operator delete" << endl;
        free(p);
    }
};

int main()
{
    /*  对象的创建
        1)Cat* p = (Cat*)Cat::operator new(sizeof(Cat)); operator new
        2)p->Cat(10);                                    construction
    */
    Cat* p = new Cat(10);
    /*  对象的销毁
        1)p->~Cat();                                     destruction
        2)Cat::operator delete(p);                       operator delete
    */
    delete p;

    return 0;
}