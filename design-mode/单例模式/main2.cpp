#include <iostream>
#include <string>
using namespace std;

class Singleton
{
public:
    static Singleton *getInstance() //创建唯一对象
    {
        ref_count++; //引用计数+1
        if (pInstance)
            return pInstance;
        pInstance = new Singleton;
        return pInstance;
    }
    void setName(const string &name)
    {
        this->m_name = name;
    }
    const string &getName()
    {
        return m_name;
    }
    void release() //引用计数为0时释放对象
    {
        if (0 == --ref_count)
        {
            delete pInstance;
            pInstance = nullptr;
        }
    }
    int reference_count() const
    {
        return ref_count;
    }
    ~Singleton()
    {
        cout << "destruction function" << endl;
        /*
        delete pInstance;//死递归
        pInstance = nullptr;
        */
    }

private:
    static Singleton *pInstance; //静态对象指针 唯一对象
    static int ref_count;
    string m_name;

private:
    Singleton() { cout << "construct function" << m_name << endl; } //私有化构造函数
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};
Singleton *Singleton::pInstance = nullptr;
int Singleton::ref_count = 0;

int main()
{
    cout << "---------->the program starts" << endl;
    //第一次创建
    Singleton *ptr = Singleton::getInstance();
    ptr->setName("cactus");
    cout << "ptr :" << ptr << " ptr->m_name : " << ptr->getName() << "ptr->ref_count:" << ptr->reference_count() << endl; // 1

    //第一次销毁
    cout << "ptr->ref_count:" << ptr->reference_count() << endl; //1
    ptr->release();// 0

    //第二次创建
    Singleton *ptr2 = Singleton::getInstance();//1
    cout << "ptr2:" << ptr2 << " ptr2->m_name: " << ptr2->getName() << "ptr2->ref_count:" << ptr2->reference_count() << endl; 

    Singleton *ptr3 = Singleton::getInstance();//2 相同地址
    cout << "ptr3:" << ptr3 << " ptr3->m_name: " << ptr3->getName() << "ptr3->ref_count:" << ptr3->reference_count() << endl; 

    //第二次销毁
    cout << "ptr3->ref_count:" << ptr3->reference_count() << endl; //2
    ptr2->release();
    cout << "ptr3->ref_count:" << ptr3->reference_count() << endl; //1
    ptr3->release();                                               //真正销毁 0

    //第三次创建
    Singleton *newPtr = Singleton::getInstance();
    newPtr->setName("pineapple");
    cout<< "newPtr:" << newPtr << ",newPtr->m_name: " << newPtr->getName() << endl;

    return 0;
}