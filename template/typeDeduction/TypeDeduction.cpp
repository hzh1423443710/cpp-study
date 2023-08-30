#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <iomanip>

using var_t = std::variant<int, long, double, std::string>;
template <class... T>
struct overloaded : public T... {
	// using引入基类的成员函数(派生类直接访问, 无需通过基类间接调用)
	using T::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

/*-------------------------------------------------------------------------------*/

struct A {
	void operator()(std::string str) {
		std::cout << __PRETTY_FUNCTION__ << "\n";
		std::cout << str << "\n";
	}
};

struct B {
	bool operator()(int a, int b) {
		std::cout << __PRETTY_FUNCTION__ << "\n";
		return a < b;
	}
};

struct C {
	void operator()(void) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

struct CC : public A, B, C {
	// CC 对象可以直接调用A,B,C的operator()函数
	using A::operator();
	using B::operator();
	using C::operator();

	/* 	//同名覆盖
		int operator()(int a, int b) {
			std::cout << __PRETTY_FUNCTION__ << "\n";
			return a + b;
		}
	 */
};

void test();

int main() {
	// test();
	std::vector<var_t> vec = {12, 15l, 1.5, "hello"};

	for (auto &&v : vec) {
		std::visit(overloaded{
					   [](auto arg) { std::cout << arg << ' '; },
					   [](double arg) { std::cout << std::fixed << arg << ' '; },
					   [](const std::string &arg) { std::cout << std::quoted(arg) << ' '; },
				   },
				   v);
	}
}

void test() {
	CC{}();
	CC{}(1, 2);
	CC{}("Hello");
}
