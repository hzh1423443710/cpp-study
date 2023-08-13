#include <iostream>

// 前置声明(只特化)
template<class... Args>
class MM;

// 特化-递归出口
template<>
class MM<>{};

// 特化
template<class T, class... Args>
class MM<T,Args...> : public MM<Args...>
{
public:
	MM() = default;
	MM(const T& data, const Args&... args) : data_(data), MM<Args...>(args...)
	{}
	T& data()
	{
		return data_;
	}
	MM<Args...>& superClass()
	{
		return *this;
	}
private:
	T data_;
};

// 前置声明
template<class... Args>
class SmallTuple;

// 特化-递归出口
template<>
class SmallTuple<>{};

// 特化
template<class T, class... Args>
class SmallTuple<T,Args...>
{
public:
	SmallTuple() = default;
	SmallTuple(const T& data, const Args&... args) : data_(data), tuple_(args...)
	{}
	T& data()
	{
		return data_;
	}
	SmallTuple<Args...>& getNext()
	{
		return tuple_;
	}
private:
	T data_;
	SmallTuple<Args...> tuple_;
};

int main(int argc, char *argv[])
{
	MM<int, float, double> m(1, 1.11f, 1.111);
	m.data() = 2;
	m.superClass().data() = 2.2f;
	m.superClass().superClass().data() = 2.22;
	std::cout << m.data() << "\n";
	std::cout << m.superClass().data() << "\n";
	std::cout << m.superClass().superClass().data() << "\n";

	SmallTuple<int, float, double> s;
	s.data() = 100;
	s.getNext().data() = 100.111f;
	s.getNext().getNext().data() = 100.111111;
	std::cout << s.data() << "\n";
	std::cout << s.getNext().data() << "\n";
	std::cout << s.getNext().getNext().data() << "\n";

	return 0;
}
