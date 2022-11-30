------main.cpp--------
#include <iostream>
using namespace std;

void print(int a);

int main()
{
    print(100);
    return 0;
}

-------print.c-------
#include <stdio.h>

#ifdef CPP
void _Z5printi(int a) //改为换名后的函数名
#else
void print(int a)
#endif
{
    printf("%d\n",a);
}

gcc -c print.c      gcc编译 
g++ -c main.cpp     g++编译
g++ main.o print.o  g++链接
出错:main.cpp中 未定义的引用 print(int), 因为print.c是用gcc编译的,没有函数名的替换.
1.如果将print.c中的函数名改为_Z5printci 就可以运行 gcc-c print.c -DCPP
2.如果都用g++编译链接,正常运行

