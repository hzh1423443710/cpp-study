#include <iostream>
using namespace std;

int main()
{
    const int i = 100;
    int* p = const_cast<int*>(&i);//c++常类型转换
                                  
    char buff[] = "0001\00012345\0001234567\000";
    struct A
    {
        char a[5];
        char b[6];
        char c[8];
    };
    //A* pa  = (A*)buff;
    A* pa  = reinterpret_cast<A*>(buff);//c++重新解释类型转换
    cout << pa->a << endl;
    cout << pa->b << endl;
    cout << pa->c << endl;

    return 0;
}

