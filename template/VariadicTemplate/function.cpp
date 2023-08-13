#include <iostream>

template<class T>
void print(const T& t)
{
	std::cout << t << " ";
}

template<class... Args>
void printArgs(const Args&... args)
{
	// 展开参数包 (逗号运算符)
//	(...,(std::cout << args << " "));
	((std::cout << args << " "), ...);
//	(..., print(args));
//	(print(args),...);
}


int main(int argc, char *argv[])
{
	printArgs(1,2,3,'\n');

	return 0;
}
