#include <iostream>

class A {
  public:
    A() {
      std::cout << "[C] constructor fired." << std::endl;
    }

    A(const A &a) {
      std::cout << "[C] copying constructor fired." << std::endl;
    }

    A(A &&a) {
      std::cout << "[C] moving copying constructor fired." << std::endl;
    }

    ~A() {
      std::cout << "[C] destructor fired." << std::endl;
    }
};

A getTempA() {
  return A();
}
 
int main(int argc, char **argv) {
  auto x = getTempA();

  return 0;
}
/* 关闭返回值优化
g++  -fno-elide-constructors .\code.cpp
[C] constructor fired.
[C] moving copying constructor fired.
[C] destructor fired.
[C] moving copying constructor fired.
[C] destructor fired.
[C] destructor fired.
*/