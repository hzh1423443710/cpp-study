#include <iostream>
#include <initializer_list>

float fun(int) {
    return 1.1f;
}

// decay to a pointer
template <class T>
void f1(T t) {
    if (std::is_same_v<T, float(*)(int)>)
        std::cout << "T == float(*)(int)\n";
    if (std::is_same_v<T, const char*>)
        std::cout << "T == const char*\n";
}
// 引用接收函数签名
template <class T>
void f2(T& t) {
    if (std::is_same_v<T, float(int)>)
        std::cout << "T == float(int)\n";
}
// 引用接收数组
template <class T, std::size_t N>
void fs1(T(&t)[N] ) {
    if (std::is_same_v<T, const char>)
        std::cout << "T == const char" << ", ParaType = const char(&)[" << N << "]";
}

int main(int argc, char* argv[])
{
    f1(fun);
    f2(fun);
    const char* pStr = "12345";
    const char str[] = "12345";
    f1(pStr);
    fs1(str);
    
    return 0;
}