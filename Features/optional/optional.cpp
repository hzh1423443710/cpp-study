#include <optional>
#include <iostream>

struct A {
    std::string s;
    A(std::string str) : s(std::move(str))  {
        std::cout << " constructed\n"; 
    }
    ~A() {
        std::cout << " destructed\n"; 
    }
    A(const A& o) : s(o.s) {
        std::cout << " copy constructed\n"; 
    }
    A(A&& o) : s(std::move(o.s)) {
        std::cout << " move constructed\n"; 
    }
    A& operator=(const A& other) {
        s = other.s;
        std::cout << " copy assigned\n";
        return *this;
    }
    A& operator=(A&& other) {
        s = std::move(other.s);
        std::cout << " move assigned\n";
        return *this;
    }
};
 
int main()
{
    std::optional<A> opt;
 
    std::cout << "Emplace:\n";
    // 由于 opt 含值，这亦将销毁该值 原地构造
    opt.emplace("Lorem ipsum dolor sit amet, consectetur efficitur. ");

    std::cout << "Assign:\n";
    opt = A("Lorem ipsum dolor sit amet, consectetur adipiscing elit nec.");
 
    std::cout << "End example\n";
}