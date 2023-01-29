#include <iostream>
using namespace std;

int main()
{
    //int& n  = 100;    //× 引用只能引用左值
    const int& rn = 100;//√ 常引用 既可以引用左值 也可以右值

    int num  = 255;
    //(1).int型的num 隐式转换为 char型num,转换的结果保存在临时变量中
    //char& rnum = num;     //× 转换后的临时变量为右值
    const char& rnum = num; //√
    cout << "rnum = " << (int)rnum << endl;// -1

    return 0;
}