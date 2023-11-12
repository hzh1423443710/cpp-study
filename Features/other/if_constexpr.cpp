#include <iostream>

// 利用SFINAE实现if constexpr

#if __cplusplus >= 201703
// 编译期if-else(std >= c++17)
template <class T>
void func17(const T& a) {
	if constexpr (std::is_same_v<int, std::decay_t<decltype(a)>>)
		std::cout << "T is int\n";
	else
		std::cout << "T is not int\n";
}

#elif __cpluspluse >= 201402

// 编译期if-else(std == c++14)
template <class T,
		  std::enable_if_t<std::is_same<int, std::decay_t<T>>::value, int> = 0>
void func14(const T& a) {
	std::cout << "T is int\n";
}

template <class T,
		  std::enable_if_t<!std::is_same<int, std::decay_t<T>>::value, int> = 0>
void func14(const T& a) {
	std::cout << "T is not int\n";
}

#else

// 编译期if-else(std == c++11)
#define REQUIRES(Cond) typename std::enable_if<(Cond), int>::type = 0

template <class T,
		  REQUIRES((std::is_same<int, typename std::decay<T>::type>::value))>
void func11(const T& a) {
	std::cout << "T is int\n";
}

template <class T,
		  REQUIRES(!(std::is_same<int, typename std::decay<T>::type>::value))>
void func11(const T& a) {
	std::cout << "T is not int\n";
}
#endif

/*---------------------------------------------------------*/
// 计时, 若有返回值要返回
#if __cplusplus >= 201703
template <class Fn, class... Args>
auto calc_time(Fn fn, Args... args) {
	std::cout << "BEGIN\n";
	if constexpr (!std::is_same_v<std::invoke_result_t<Fn, Args...>, void>) {
		auto ret = fn(args...);
		std::cout << "END\n";
		return ret;
	} else {
		fn(args...);
		std::cout << "END\n";
	}
}

void test_example() {
	std::cout << "-- 1.\n";
	auto ret = calc_time(
		[](int a, int b) {
			printf("calc %d + %d\n", a, b);
			return a + b;
		},
		100, 10);
	std::cout << "ret = " << ret << "\n";
	std::cout << "-- 2.\n";
	calc_time([]() { std::cout << "No return value\n"; });
}
#endif

void test_impl() {
#if __cplusplus >= 201703
	func17(int{});
	func17(float{});
#elif __cpluspluse >= 201402
	func14(int{});
	func14(float{});
#else
	func11(int{});
	func11(float{});
#endif
}

int main(int argc, char* argv[]) {
	std::cout << __cplusplus << "\n";
	test_example();
	// test_impl();

	return 0;
}