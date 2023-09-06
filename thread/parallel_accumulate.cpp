#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>

template <class Iterator, class Ret>
Ret parallel_accumulate(Iterator first, Iterator last, Ret init) {
	auto length = last - first;
	if (!length) return init;

	const int tasks_per_thread = 100'0000;	// the number of calculations per threads
	const int max_threads = (length + tasks_per_thread - 1) / tasks_per_thread;	 // 向上取整
	const int hardware_threads = std::thread::hardware_concurrency();
	const int nums_thread = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	std::vector<std::thread> threads(nums_thread - 1);
	std::vector<Ret> results(nums_thread);

	const size_t block_size = length / nums_thread;
	Iterator block_start = first;
	Iterator block_end = block_start;
	auto calc_one_block = [](Iterator first, Iterator last, Ret& result) {
		result = std::accumulate(first, last, Ret{});
	};

	for (int i{}; i < threads.size(); ++i) {
		std::advance(block_end, block_size);
		threads[i] = std::thread(calc_one_block, block_start, block_end, std::ref(results[i]));
		block_start = block_end;
	}
	calc_one_block(block_end, last, std::ref(results[nums_thread - 1]));
	// reclaim child thread
	std::for_each_n(threads.begin(), threads.size(), std::mem_fn(&std::thread::join));
	return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char* argv[]) {
	std::cout << __FUNCTION__ << "\n";
	std::vector<short> arr(10'000'0000);
	srand(time(NULL));
	// std::iota(arr.begin(), arr.end(), 1);
	std::generate(arr.begin(), arr.end(), []() { return rand() % 1000; });

	std::cout << "------> start_cal\n";
	auto t1 = clock();
	std::cout << parallel_accumulate(arr.begin(), arr.end(), 0ull) << "\n";
	auto t2 = clock();
	std::cout << std::accumulate(arr.begin(), arr.end(), 0ull) << "\n";
	auto t3 = clock();
	std::cout << "parallel accumulate = " << t2 - t1 << "\n";
	std::cout << "std::accumulate = " << t3 - t2 << "\n";

	return 0;
}
