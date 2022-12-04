#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    ostringstream outstr;    //向字符串缓冲区写数据
    int num = 100;
    float score = 79.6f;
    char name[20] = "cactus";
    outstr << num << " " << score <<  " " << name;

    cout << outstr.str() << endl;

    istringstream inputstr;  //从字符串缓冲区读数据
    inputstr.str("1234 88.8 Peekaboo");
    inputstr >> num >> score >> name;
    cout << num << " " << score << " " << name << endl;


    return 0;
}