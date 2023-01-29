#include <stdio.h>

#ifdef CPP
void _Z5printi(int a) //改为换名后的函数名
#else
void print(int a)
#endif
{
    printf("%d\n",a);
}
