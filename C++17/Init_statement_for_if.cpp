#include <iostream>
#include <map>

// if/switch initialization

void test();
// 嵌套structured bindings
void test2();

int main()
{
    test2();

    return 0;
}

void test()
{
    if(int a = 10,b = 20; a + b > 20) {
        std::cout << a << "+" << b << ">" << 20 << std::endl;
    }
}

void test2()
{
    std::map<std::string, int> map;
    if(auto[iter,ok] = map.insert(std::make_pair("Moss",1234)); ok) {
        std::cout << iter->first << " " << iter->second << std::endl;
    }
    if (auto [x, y] = std::make_tuple(1, 2); x + y > 1) {
        // 执行语句
    }
}