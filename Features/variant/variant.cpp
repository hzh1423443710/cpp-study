#include <iostream>
#include <string>
#include <variant>

// 打包Lambda 重载调用
template <class... CallObjs>
struct match : public CallObjs... {
	using CallObjs::operator()...;
};
template <class... T>
match(T...) -> match<T...>;

int main(int argc, char *argv[]) {
	using namespace std;
	variant<int, float, string> v;

	v = 3.14f;
	std::visit(match{[](int n) { cout << "v = " << n << "\n"; },
					 [](float f) { cout << "v = " << f << "\n"; },
					 [](const string &str) { cout << "v = " << str << "\n"; }},
			   v);

	return 0;
}