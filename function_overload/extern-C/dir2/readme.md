# C/C++混合编程
----------main.c------  
void print(int a);  
  
int main()  
{  
    print(100);  
    return 0;  
}  
----------print.cpp------  
#include <stdio.h>  
void print(int a)  
{  
    printf("%d\n",a);  
}  
  
  
gcc -c main.c  
g++ -c print.cpp   
g++ *.o  
出错:    
    main,c中,找不到函数的定义,因为print.cpp用的是g++编译 print函数会换名为 _Z5printi ,只有_Z5printi()的定义  
而没有print()的定义  
  
解决:  
    1.extern "C" 表示用使用C语言的编译方式(使用extern "C"就不可以重载了,因为函数没有换名)  
----------print.cpp------  
#include <stdio.h>  
extern "C" void print(int a)  
{  
    printf("%d\n",a);  
}  
    2.将main.c里的print改为_Z5printi ,因为print.cpp是C++语言编译的,没有print的定义,但是有_Z5printi的定义  
