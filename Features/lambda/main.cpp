#include <iostream>

/*
	https://cppinsights.io/
	Lambda 捕获的变量 会变成 匿名类的成员变量
	Lambda 内部有operator()的实现

	non-mutable lambda的operator()是const的
	mutable lambda的operator()会去掉const的

	捕获引用不加mutable也可以修改
		是因为const限定引用不可以修改其指针的指向,指向的内容当然可以修改
*/

int main(int argc, char* argv[]) {
	int a = 10;
	int b = 20;
	auto call = [&a, b]() mutable {
		a = 100;
		b = 200;
	};
	call();
	std::cout << a << "," << b << "\n";

	return 0;
}