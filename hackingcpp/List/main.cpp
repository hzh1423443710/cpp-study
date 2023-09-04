#include <list>

#include "mylist.hpp"

int main(int argc, char* argv[]) {
	using namespace hzh;

	List<int> list;
	for (int i{}; i < 5; ++i) {
		list.insert(list.begin(), 5 - i);
	}
	std::cout << "l1 size = " << list.size() << "\n";
	std::cout << "---------------------------\n";

	List l2(std::move(list));
	std::cout << "l1 size = " << list.size() << "\n";
	std::cout << "l2 size = " << l2.size() << "\n";
	std::cout << "---------------------------\n";

	List<int> l3;
	l3 = std::move(l2);
	std::cout << "l1 size = " << list.size() << "\n";
	std::cout << "l2 size = " << l2.size() << "\n";
	std::cout << "l3 size = " << l3.size() << "\n";
	std::cout << "---------------------------\n";
	for (auto& x : l3) {
		std::cout << x << " ";
	}
	std::cout << "\n";

	return 0;
}
