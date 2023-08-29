#include <iostream>
#include <memory>

class A
{
public:
    virtual ~A() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
};

class B : public A
{
public:
    ~B() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }
};

int main() 
{
    std::unique_ptr<A> pa = std::make_unique<B>();
}

