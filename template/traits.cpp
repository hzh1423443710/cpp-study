#include <iostream>

// -- 萃取
template <class T>
struct sum_t {};

template <>
struct sum_t<int> {
	using type = long long;
};

template <>
struct sum_t<char> {
	using type = int;
};

// -- 自定义累加[不溢出]
template <class T>
auto accumulate(const T* p1, const T* p2) {
	typename sum_t<T>::type sum{};
	while (p1 != p2) sum += *p1++;
	return sum;
}

// -- 自定义begin() end()
template <class T, size_t size>
constexpr T* begin(T (&arr)[size]) {
	return arr;
}

template <class T, size_t size>
constexpr T* end(T (&arr)[size]) {
	return arr + size;
}

int main(int argc, char* argv[]) {
	int arr[]{1000000000, 2000000000, 1000000000};
	char str[] = "ddd";

	auto x = accumulate(begin(arr), end(arr));
	auto y = accumulate(begin(str), end(str));

	std::cout << x << "\n";
	std::cout << y << "\n";

	return 0;
}