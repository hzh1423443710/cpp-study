#include <iostream>
#include <type_traits>
#include <string>

// -- 1.问题 
class Cat_1
{
public:
    // 构造函数
    template<class T>
    Cat_1(T&& t) {
        std::cout << "construct\n";       
        // id = t;
    }
    // 拷贝构造
    Cat_1(const Cat_1& other) {
        std::cout << "copy\n";
        // id = other.id;
    }
private:
    int id;
};

// -- 2.解决 <- 普通构造参数不可能为自己
class Cat_2
{
public:
    // 构造函数[如果T不是int, enable_if_t<false>为无效模板 进而匹配拷贝构造]
    template<class T, class T2 = typename std::enable_if_t< std::is_convertible_v<T, int> >>
    Cat_2(T&& t) {
        std::cout << "construct\n";
        id = t;
    }
    // 拷贝构造
    Cat_2(const Cat_2& other) {
        std::cout << "copy\n";
        id = other.id;
    }
private:
    int id;
};

void test_Cat1_question() {
    // 实例化2种构造函数
    Cat_1 a(1); // 调用构造函数, 加const后不会出错
    Cat_1 b(a); // 匹配构造函数, 万能引用比拷贝构造的const更匹配

    // error: Cat_1 不能转为 int
}

void test_Cat2_solution() {
    // 只实例化1种构造函数
    Cat_2 a(1); // 调用构造函数
    Cat_2 b(a); // 匹配拷贝构造
}

int main()
{
    test_Cat2_solution();

    return 0;
}
