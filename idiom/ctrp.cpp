/*
	奇异递归模板模式 Curiously Recurring Template Pattern
	用于实现:编译期多态(基类暴露接口,派生类实现接口)
	https://en.cppreference.com/w/cpp/language/crtp
*/
#include <iostream>

template <class Z>
class Y {};
// 派生自模板类 Y 并且以模板参数 Z=X 实例化类模板 Y
class X : public Y<X> {};

template <class Derived>
class Base {
public:
	void name() { static_cast<Derived*>(this)->impl(); }
};

class D1 : public Base<D1> {
public:
	void impl() { std::cout << "D1::impl()\n"; }
};

class D2 : public Base<D2> {
public:
	void impl() { std::cout << "D2::impl()\n"; }
};

int main(int argc, char* argv[]) {
	D1 d1;
	D2 d2;
	d1.name();
	d2.name();

	return 0;
}