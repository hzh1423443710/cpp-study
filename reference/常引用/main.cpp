#include <iostream>
using namespace std;

int main()
{
    //int& n  = 100;    //�� ����ֻ��������ֵ
    const int& rn = 100;//�� ������ �ȿ���������ֵ Ҳ������ֵ

    int num  = 255;
    //(1).int�͵�num ��ʽת��Ϊ char��num,ת���Ľ����������ʱ������
    //char& rnum = num;     //�� ת�������ʱ����Ϊ��ֵ
    const char& rnum = num; //��
    cout << "rnum = " << (int)rnum << endl;// -1

    return 0;
}