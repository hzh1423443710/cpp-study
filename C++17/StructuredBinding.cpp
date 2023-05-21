#include <iostream>
#include <string>
#include <tuple>
// 结构化绑定

// 绑定数组
void test_bindArray();
// 绑定元组 不必再使用get访问
void test_bindTuple();
// 绑定结构返回值
struct Data {
    std::string str;
    int id;
};
void test_bindRetData();
Data getData();

int main()
{
    test_bindArray();
    test_bindTuple();
    test_bindRetData();

    return 0;
}

void test_bindArray()
{
    //1.
    int arr[]{1,2};
    auto [x,y] = arr;
    std::cout << x << " " << y << std::endl;
    //2.
    auto[a,b,c] = std::make_tuple(1,1.1,'c');
    std::cout << a << " " << b << " " << c << std::endl;
}

void test_bindTuple()
{
    std::string str = "tuple";
    int num = 100;
    double s = 66.6;
    std::tuple<std::string,int,double> t(str,num,s);
    
    auto[str2,num2,s2] = t;
    std::cout << str2 << " " << num2 << " " << s << std::endl;
    // std::tie
    auto[a,b,c] = std::tie(str,num,s);
    std::cout << a << " " << b << " " << c << std::endl;
}

void test_bindRetData()
{
    auto[str,id] = getData();
    std::cout << str << " " << id << std::endl;
}

Data getData()
{
    Data d;
    d.id = 123;
    d.str = "hello";
    return d;
}