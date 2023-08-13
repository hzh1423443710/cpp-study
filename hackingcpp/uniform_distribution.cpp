#include <iostream>
#include <random>
#include <chrono>

int main(int argc, char *argv[])
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
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

	return 0;
}
