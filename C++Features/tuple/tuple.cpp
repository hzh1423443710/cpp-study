#include <iostream>
#include <tuple>

// tie, 结构化绑定
// std::ignore
// tuple_cat tuple_size() tuple_element()

struct Person
{
    int age;
    float height;
    std::string name;
    friend std::ostream& operator<<(std::ostream& out, const Person& it) {
        printf("%s %d %.1f", it.name.c_str(), it.age, it.height);
        return out;
    }
};

void test_tie();
// 结构化绑定
void test_struct_bind();
// 拼接tuple
void test_tuple_cat();
void test_other();

int main()
{
    // test_struct_bind();
    // test_tie();
    // test_tuple_cat();
    test_other();

    return 0;
}

void test_tie()
{
    std::tuple<int, double, std::string> person { 25, 175.5, "John" };
    Person p;
    // -- tie
    std::tie(p.age, p.height, p.name) = std::move(person);
    std::cout << p << "\n";
}

void test_struct_bind()
{
    std::tuple<int, double, std::string> person { 25, 175.5, "John" };

    auto [age, height, name] = std::move(person);
    Person p;
    p.height = height;
    p.age = age;
    p.name = std::move(name);
    std::cout << p << "\n";
}
void test_tuple_cat()
{
    // t_cat = t + t1;
    auto t = std::make_tuple("Moss", "Shanxi");     // name, from
    auto t1 = std::make_tuple(25, 175.5, "computer");// age, height, major
    auto t_cat = std::tuple_cat(t,t1);

    // -- std::ignore
    Person p;
    std::tie(p.name, std::ignore, p.age, p.height, std::ignore) = t_cat;
    std::cout << p << "\n";
}

void test_other()
{
    using MyTuple = std::tuple<int,double,std::string,int>;
    // 获取元素个数
    std::cout << "tuple size = " << std::tuple_size<MyTuple>::value << "\n";
    // 给定索引获取类型
    if (std::is_same<double, std::tuple_element<1, MyTuple>::type>::value)
        std::cout << "Element Type at Index 1 is double\n";
}