#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <functional>
#include <iterator>

void test_1();
void test_2();


int main(int argc, char *argv[])
{
	test_2();

	return 0;
}

void test_1()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	// 引擎
	std::mt19937 mt(seed);      // unsigned 32bit
	std::cout << mt() << "\n";  // operator()

	// 均匀分布
	std::uniform_int_distribution<int> distr1(1,6);
	std::cout << distr1(mt) << "\n";

	seed = std::random_device{}();
	std::random_device::result_type x; // 重新播种

	mt.seed(seed);
	// 均匀分布
	std::uniform_real_distribution<float> distr2(0.0f, 1.0f);
	std::cout << distr2(mt) << "\n";
}

void test_2()
{
	std::default_random_engine e(time(nullptr));
	std::uniform_int_distribution<int> dist(0,100);
	std::vector<int> arr(10);

	auto generator = std::bind(dist, e);
	std::generate_n(arr.begin(), arr.size(), generator);
	std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "});
}