#include <iostream>
using namespace std;

int fun()
{
    int num  = 100;
    cout  << "&num = " << &num << endl;
    return num;
}

int main()
{
    int a = fun();      //(1).num��ֵ����ʱ����(2).num����(3).��ʱ������ֵ��a
    cout << "a = " << a << endl;

    //int& rf = fun();    //�� error ��ͨ����ֻ�ܽ�����ֵ
    const int& rf = fun();//�� 
    cout << "&rf = " << &rf << " , rf = " << rf << endl;//��ַ��һ��

    return 0;
}