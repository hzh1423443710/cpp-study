#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>

void testInput();
void testSeqence();

template<class T>
class ascending_seqence
{
private:
	using stroage_t = std::vector<T>;
public:
	using value_type = T;
	using size_type = typename stroage_t::size_type;

public:
//	void insert(const value_type& value) {
//		seq_.insert(std::lower_bound(seq_.begin(), seq_.end(), value), value);
//	}
	void insert(const value_type& value) {
		seq_.insert(std::upper_bound(seq_.begin(), seq_.end(), value), value);
	}
	auto begin() const {
		return seq_.begin();
	}
	auto end() const {
		return seq_.end();
	}
	size_type size() const {
		return seq_.size();
	}
	value_type operator[](size_type i){
		return seq_[i];
	}
private:
	stroage_t seq_;
};

int main()
{
	testSeqence();
//	test_input();

	return 0;
}

void testSeqence()
{
	ascending_seqence<int> seq;
	const int arr[] = {1,4,7,11};
	for (auto&& v : arr) {
		seq.insert(v);
	};
	seq.insert(5);
	for (auto&& v : seq) {
		std::cout << v <<" ";
	}
	std::cout << "\n";
}

void testInput()
{
	using namespace std;
	// 1.
	cout << "Please a string char:";
	string buff;
	// 忽略输入流一行字符
//	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// Ctrl + z  std::cin -> eof
	cin.ignore(std::numeric_limits<std::streamsize>::max(), EOF);
	if (cin.eof())
		cin.clear();
	if (cin.good())
		cin >> buff;
	cout << "buff:" << buff << "\n";

	// 2.
	cout << "Please a integer number:";
	cin.clear();
	int n;
	cin >> n;
	if (cin.fail()) {
		cout << "cin's failbit is set\n";
		// Solution
		cin.clear(); // clear all error status
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
	}

	if (cin.good())
		cout << "n = " << n;
}








