#include <iostream>
using namespace std;

int add(int a,int b)
{
    return a+b;
}

int main()
{
    int a = 100;
    int& ra = a;
    int* pra = &ra;
    //int&* rpa = &ra;          //×  不存在指向引用的指针
    int*& rpa  = pra;           //√  存在指针的引用

    //int& &rra = ra;           //×  不存在引用的引用
    int& rra = ra;              //√  一般引用

    int x = 1,y = 2,z = 3;
    int arr[] = {x,y,z}; 
    //int& rarr[3] = {x,y,z};   //× 不存在用的数组 
    int (&rarr)[3] = arr;       //√ 存在数组的引用

    int (*pAdd)(int,int) = add; //函数指针
    int (&rAdd)(int,int) = add; //函数引用
    cout << rAdd(10,20) << endl;

    return 0;
}