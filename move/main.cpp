#include <iostream>
#include <cstring>
#include <string>

class String
{
	friend std::ostream& operator << (std::ostream& out, const String& it) {
		if (it.has_value())
			out << it.data;
		return out;
	}
public:
	String() :data(nullptr), size(0) {
		std::cout << "construction" << std::endl;
	}
	String(const char* str) {
		size = strlen(str) + 1;
		data = new char[size];
		memcpy(data, str, size);
		std::cout << "construction" << std::endl;
	}
	String(const String& other) {
		size = other.size;
		data = new char[size];
		memcpy(data, other.data, size);
		std::cout << "copy construction" << std::endl;
	}
	String(String&& other) noexcept :String() {
		size = other.size;
		data = other.data;
		other.data = nullptr;
		other.size = 0;
		std::cout << "move construction" << std::endl;
	}
	String& operator = (const String& other) noexcept {
		std::cout << "assign construction" << std::endl;
		if (this == &other)
			return *this;
		delete data;
		size = other.size;
		data = new char[size];
		memcpy(data, other.data, size);
		return *this;
	}
	String& operator = (String&& other) noexcept {
		std::cout << "move assign construction" << std::endl;
		if (this == &other)
			return *this;
		size = other.size;
		data = other.data;
		other.data = nullptr;
		other.size = 0;
		return *this;
	}
	bool has_value() const {
		return data != nullptr;
	}
	const char* c_str() const {
		return data;
	}
	size_t Size() const {
		return this->size;
	}
	~String()
	{
		delete[] data;
		data = nullptr;
		std::cout << "destruction" << std::endl;
	}

private:
	char* data;
	size_t size;
};

String test(const char* str)
{
	String s(str);
	std::cout << &s << std::endl;
	return s;
}

void reference(int& s)//接受左值
{
	std::cout << "left reference" << std::endl;
}

void reference(int&& s)//接受右值
{
	std::cout << "right reference" << std::endl;
}

template<typename T>
void function(T&& arg) {
	reference(std::forward<T>(arg));
}

template<typename T>
void print(T& t) {
	std::cout << "lvalue" << std::endl;
}
template<typename T>
void print(T&& t) {
	std::cout << "rvalue" << std::endl;
}

template<typename T>
void TestForward(T&& v) {
	print(v);					//l:左值 print(T& t)
	print(std::forward<T>(v));	// :取决于 v 的实参是左值还是右值 static_cast<T&&>(_Arg);
	print(std::move(v));		//r:右值 print(T&& t)
}

void test() {
	int x = 1;
	TestForward(1);//实参为右值 lrr
	std::cout << "------" << std::endl;
	TestForward(x);//实参为左值 llr
	std::cout << "------" << std::endl;
	TestForward(std::forward<int>(x));//实参为右值 lrr ,static_cast<int&&>(_Arg);
	std::cout << "------" << std::endl;
	TestForward(std::forward<int&>(x));//实参为左值 llr ,static_cast<int& &&>(_Arg);
	std::cout << "------" << std::endl;
	TestForward(std::forward<int&&>(x));//实参为右值 lrr ,static_cast<int&& &&>(_Arg);
}

int main()
{
	String str;
	String str2("Hello Moss");
	str = std::move(str2);
	std::cout << str << std::endl;

	return 0;
}