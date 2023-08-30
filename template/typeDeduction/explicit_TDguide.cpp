#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

template <class T>
struct Container {
	// 1. 从构造函数 隐式推导出 container<T>
	explicit Container(const T& t) { std::cout << __PRETTY_FUNCTION__ << "\n"; }
	// 2. 隐式推导
	Container(const std::initializer_list<T>& init) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

	// 3. 无法隐式推导出 需要显式推导指引
	template <class Iter>
	Container(Iter beg, Iter end) {
		std::cout << __PRETTY_FUNCTION__ << "\n";
	}
};

// 显式推导指引
template <class Iter>
Container(Iter beg, Iter end) -> Container<typename Iter::value_type>;

int main(int argc, char* argv[]) {
	Container c1(100); // 隐式推导指引

	std::vector<int> v{1, 2, 3};
	Container c2(v.begin(), v.end()); // 显式推导指引

	Container c3 = {1, 2, 3}; // 隐式推导指引

	return 0;
}