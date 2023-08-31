#include <iostream>
#include "MyAny.hpp"

void testInitAndMove();
void testCopyAndAssignment();

int main(int argc, char* argv[]) {
	testInitAndMove();
	std::cout << "\n-------------------------------------------\n";
	testCopyAndAssignment();
	return 0;
}

void testInitAndMove() {
	MyAny a1 = 100;
	MyAny a2;
	a2 = std::move(a1);
	if (a1.has_value()) {
		std::cout << a1.value<int>() << "\n";
	}
	if (a2.has_value()) {
		try {
			std::cout << "a2 = " << a2.value<int>() << "\n";
			std::cout << "a2 = " << a2.value<float>() << "\n";
		} catch (const std::runtime_error& e) {
			std::cout << e.what();
		}
	}
}

void testCopyAndAssignment() {
	MyAny a1 = 100;
	MyAny a2(a1);
	a1 = 2000;
	try {
		std::cout << "a1 = " << a1.value<int>() << "\n";
		std::cout << "a2 = " << a2.value<int>() << "\n";
	} catch (const std::runtime_error& e) {
		std::cout << e.what() << "\n";
	}
	a2 = 3.14f;
	if (a2.has_value()) std::cout << "a2 = " << a2.value<float>() << "\n";
	MyAny a3;
	if (a3.has_value()) std::cout << "a3 = " << a3.value<float>() << "\n";
	a3 = a2;
	if (a3.has_value()) std::cout << "a3 = " << a3.value<float>() << "\n";
}