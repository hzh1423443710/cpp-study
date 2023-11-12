#include <iostream>
#include <type_traits>
#include <vector>
#include <map>

/*
 *  SFINAE:
 *      std::enable_if<Cond,type=void>	[用在函数模板]
 *      std::void_t<typename...>        [用在类模板特化]
 * 		std::void_t<>只要类型列表可行就返回void
 *
 *  Example:
 *      myany 和 myfunciton 的实现 std::enable_if_t
 *      Any和Function的 有参构造函数 参数是万能引用类型,可以接受任意类型
 *          SFINAE 避免了 拷贝构造和移动构造 进入有参构造函数
 *      Any和Function的 对象赋值(operator=) 参数是万能引用类型, 可以接受任意类型
 *          SFINAE 避免了 拷贝赋值和移动赋值 进入对象赋值函数
 */

// Example1:
struct SS {
	using value_type = int;
	void push_back(value_type val) {}
};

// 通过特化判断 是否有 push_back函数和value_type
template <class T, class = void>
struct has_push_back {
	static constexpr bool value = false;
};

template <class T>
struct has_push_back<T, std::void_t<decltype(std::declval<T>().push_back(
							std::declval<typename T::value_type>()))>> {
	static constexpr bool value = true;
};

// Example2:
class A {};

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
								  decltype(std::declval<T>().end())>>
	: std::true_type {};

void test_example1() {
	std::cout << has_push_back<int>::value << "\n";
	std::cout << has_push_back<std::string>::value << "\n";
	std::cout << has_push_back<std::vector<int>>::value << "\n";
	std::cout << has_push_back<SS>::value << "\n";
}

void test_example2() {
	std::cout << is_iterable<std::vector<double>>::value << '\n';
	std::cout << is_iterable<std::map<int, double>>::value << '\n';
	std::cout << is_iterable<double>::value << '\n';
	std::cout << is_iterable<A>::value << '\n';
}

int main(int argc, char* argv[]) {
	std::boolalpha(std::cout);
	// test_example1();
	test_example2();

	return 0;
}