#include <iostream>
using namespace std;

int main()
{
    //1.const_cast :const int* -> int*
    const int i = 100;
    int* p = const_cast<int*>(&i);
                                  
    //2.dynamic_cast 父类指针指向子类,不加也可以,自动转


    //3.static_cast 子类指针指向父类 

    //4.reinterpret_cast :相当于C语言的强转,不同类型之间的强转 int* -> char*
    char buff[] = "0001\00012345\0001234567\000";
    struct A
    {
        char a[5];
        char b[6];
        char c[8];
    };
    //A* pa  = (A*)buff;
    A* pa  = reinterpret_cast<A*>(buff);
    cout << pa->a << endl;
    cout << pa->b << endl;
    cout << pa->c << endl;

    return 0;
}

