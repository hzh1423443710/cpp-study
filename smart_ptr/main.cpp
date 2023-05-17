#include <iostream>
#include <memory>

// shared_ptr 循环引用问题

#define USE_WEAKPTR 1

class Child;    
using ChildPtr = std::shared_ptr<Child>;
using WeakChildPtr = std::weak_ptr<Child>;
class Parent
{
public:
    Parent()
    {
        std::cout << "Parent\n";
    }
    ~Parent()
    {
        std::cout << "~Parent\n";
    }

public:
#if USE_WEAKPTR
    WeakChildPtr pChild;
#else
    ChildPtr pChild;
#endif
};

using ParentPtr = std::shared_ptr<Parent>;
using WeakParentPtr = std::weak_ptr<Parent>;
class Child
{
public:
    Child()
    {
        std::cout << "Child\n";
    }
    ~Child()
    {
        std::cout << "~Child\n";
    }
public:
#if USE_WEAKPTR
    WeakParentPtr pParent;
#else
    ParentPtr pParent;
#endif
};

void test()
{
    ParentPtr father(new Parent);
    ChildPtr child(new Child);
    father->pChild = child;
    child->pParent = father;
    // shared_ptr 引用计数为各 2  释放时引用计数-1 > 0
    // weak_ptr   引用计数为各 1  释放时引用计数-1 = 0

    std::cout << father->pChild.use_count() << std::endl; // 2
    std::cout << child->pParent.use_count() << std::endl; // 2
}

int main()
{
    test();
}