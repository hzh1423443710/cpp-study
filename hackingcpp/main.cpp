#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <set>
#include "bstree.hpp"

class MM
{
	friend std::ostream& operator<<(std::ostream& out, const MM& m) {
		out << m.val_ << ", ";
		return out;
	}
public:
	explicit MM(int val = 0) : val_(val) {
		std::cout << "construction, " << val_ << ", " << this << "\n";
	}
	MM(const MM& other) {
		val_ = other.val_;
		std::cout << "copy construction, " << val_ << ", " << this << "\n";
	}
	~MM() {
		std::cout << "destruction, " << val_ << ", " << this << "\n";
	}
	bool operator<(const MM& other) const {
		return val_ < other.val_;
	}

private:
	int val_;
};

void test();

int main(int argc, char *argv[])
{
	std::set<int>::iterator it;
	BSTree<int> tree{1,4,7,2,5,8,3,6,9,0};
	tree.insert(-1);
	tree.insert(11);


	BSTree<int> tree2(std::move(tree));
//	tree2 = std::move(tree);

	std::cout << "size1 = " << tree.size() << "\n";
	std::cout << "size2 = " << tree2.size() << "\n";

	if (!tree.empty())
		tree.printTree();

	if (!tree2.empty())
		tree2.printTree();


	std::cout << std::string(30, '-') << "\n";
}

void test()
{
	using Tree = BSTree<int>;
	Tree t;
	int num;
	while (true) {
		std::cout << "Please Number:";
		std::cin >> num;
		if (std::cin.fail() && !std::cin.eof()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Please Enter Again!\n";
			continue;
		}
		if (std::cin.eof())
			break;
		t.insert(num);
	}

	Tree t2;
	t2 = t;
	t.printTree();
	t2.printTree();

	std::cout << "\n";
}
