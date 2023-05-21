#include <iostream>
#include <memory>

// 构造函数中抛出异常 不会构造出对象也就不会析构对象
// 注意抛出异常的构造函数中,是否有申请动态内存的操作(声明顺序!!!)

class Base
{
public:
    Base(int a):m_v(new int(a)) {
        std::cout << "Base Construct" << std::endl;
    }
    ~Base() {
        delete m_v;
        std::cout << "Base Destroy" << std::endl;
    }
private:
    int* m_v;
};

class Evil
{
public:
    Evil() { 
        throw 10; 
    }
    ~Evil() {}
};

class Derived : public Base
{
public:
    Derived(int a) :Base(a), m_ptr(new char[100] {"Hello World"}) {
        std::cout << "Derived Construct" << std::endl;
    }
    ~Derived() {
        std::cout << "Derived Destroy" << std::endl;
        if (m_ptr) {
            delete[] m_ptr;
            std::cout << "delete m_ptr\n";
        }
    }
private:
// 修改声明顺序!
#if 1
    Evil m_ev;              // 先throw Derived不会构造出来
    char* m_ptr = nullptr;  // 后new
#else
    char* m_ptr = nullptr;  // 先new  
    Evil m_ev;              // 后throw Derived也不会构造出来 但m_ptr new 出的内存不会被delete
#endif
};

void test1()
{
    Base* pf = new Base(100);       // 不会析构
    throw 1001;   // 抛出异常
}
void test2()
{
    std::unique_ptr<Base> p_Base = std::make_unique<Base>(100);// 会析构
    throw 1002;   // 抛出异常
}

int main()
{
    try {
        // test1(); // 不会析构
        // test2(); // 会析构
        Derived m(100);
    } catch (int e) {
        std::cout << e << std::endl;
    }   

    return 0;
}
