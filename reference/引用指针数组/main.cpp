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
    //int&* rpa = &ra;          //��  ������ָ�����õ�ָ��
    int*& rpa  = pra;           //��  ����ָ�������

    //int& &rra = ra;           //��  ���������õ�����
    int& rra = ra;              //��  һ������

    int x = 1,y = 2,z = 3;
    int arr[] = {x,y,z}; 
    //int& rarr[3] = {x,y,z};   //�� �������õ����� 
    int (&rarr)[3] = arr;       //�� �������������

    int (*pAdd)(int,int) = add; //����ָ��
    int (&rAdd)(int,int) = add; //��������
    cout << rAdd(10,20) << endl;

    return 0;
}