#include <iostream>
#include <numeric>
#include <vector>

template <class T>
void f2(T&& t) {
	if (std::is_same_v<T, int&>) std::cout << "T == int&\n";
	if (std::is_same_v<T, const int&>) std::cout << "T == const int&\n";

	if (std::is_same_v<T, int>) std::cout << "T == int\n";
	if (std::is_same_v<T, const int>) std::cout << "T == const int\n";
}

template <class T>
void f3(T t) {
	if (std::is_same_v<T, int>) std::cout << "T == int\n";
	if (std::is_same_v<T, int&>) std::cout << "T == int&\n";
	if (std::is_same_v<T, const int&>) std::cout << "T == const int&\n";

	if (std::is_same_v<T, int*>) std::cout << "T == int*\n";
	if (std::is_same_v<T, const int*>) std::cout << "T == const int*\n";
	if (std::is_same_v<T, int* const>) std::cout << "T == int* const\n";
	if (std::is_same_v<T, const int* const>) std::cout << "T == const int* const\n";
}

void test_case2();
void test_case3();

int main(int argc, char* argv[]) {
	// test_case2();
	// test_case3();
	const char name[] = "hzh";
	const char* pName = "hzh";

	std::cout << (void*)name << "\n";
	std::cout << (void*)pName << "\n";
	std::cout << (void*)"hzh"
			  << "\n";

	return 0;
}

void test_case2() {
	int a = 10;			  // int
	const int ca = 100;	  // const int
	const int& rca = ca;  // cosnt int&
	f2(a);				  // T == int&
	f2(ca);				  // T == const int&
	f2(rca);			  // T == const int&
	f2(10);				  // T == int
}

void test_case3() {
	int a = 10;			 // int
	int& ra = a;		 // int&
	const int ca = 100;	 // const int
	const int& cra = a;	 // const int&
	f3(a);				 // T == int
    f3(ra);				 // T == int
	f3(ca);				 // T == int
	f3(cra);			 // T == int

    int* p              ;				// int*
	const int* cp1 = &a;		// const int*
	int* const cp2 = &a;		// int* const
	const int* const ccp = &a;	// cnst int* const
	f3(p);						// T == int*
	f3(cp1);					// T == const int*
	f3(cp2);					// T == int *
	f3(ccp);					// T == const int*	
}
