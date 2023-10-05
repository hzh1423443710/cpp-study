#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <execution>
#include <functional>
#include <future>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <numeric>
#include <shared_mutex>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#include "test.hpp"

template <typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
	if (input.empty()) {
		return input;
	}

	std::list<T> result;
	result.splice(result.begin(), input, input.begin());  // 1
	T const& pivot = *result.begin();					  // 2
	auto divide_point =
		std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });	// 3
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(),
					  divide_point);							   // 4
	auto new_lower(sequential_quick_sort(std::move(lower_part)));  // 5
	auto new_higher(sequential_quick_sort(std::move(input)));	   // 6
	result.splice(result.end(), new_higher);					   // 7
	result.splice(result.begin(), new_lower);					   // 8

	return result;
}

int main1(int argc, char* argv[]) {

	// std::list<int> l{1, 4, 7, 2, 5, 8, 3, 6, 9, 0};
	// auto list = sequential_quick_sort(l);
	// for (auto& x : list) {
	// 	std::cout << x << " ";
	// }
	// std::cout << "\n";
	std::list<int> l1{1, 4, 7, 2, 5, 8, 3, 6, 9, 0};
	std::partition(l1.begin(), l1.end(), [](auto& x) { return x <= 6; });
	for (auto& x : l1) {
		std::cout << x << " ";
	}
	std::cout << "\n";

	return 0;
}

threadsafe_queue<int> s;

std::pair<std::thread::id, int> producer(int num) {
	for (std::size_t i = 0; i < num; ++i) {
		int product = rand() % 100 + 1;
		s.push(product);
	}
	std::cout << std::this_thread::get_id() << " produce end\n";
	return {std::this_thread::get_id(), num};
}

std::pair<std::thread::id, int> consumer() {
	int cnt{};
	std::cout << std::this_thread::get_id() << " cur = " << s.size() << "\n";
	while (!s.empty()) {
		auto ret = s.wait_and_pop();
		cnt++;
	}
	
	std::cout << "  " << std::this_thread::get_id() << " consume end\n";
	return {std::this_thread::get_id(), cnt};
}

int main(int argc, char* argv[]) {
	
	srand(time(nullptr));
	std::vector<std::thread> producers(2);
	std::vector<std::thread> consumers(5);
	std::unique_lock<std::shared_mutex> m;

	using Ret = std::pair<std::thread::id, int>;
	using ProduSig = Ret(int);
	using ConsuSig = Ret();
	std::vector<std::packaged_task<ProduSig>> task_producer(producers.size());
	std::vector<std::packaged_task<ConsuSig>> task_consumer(consumers.size());
	std::vector<std::future<Ret>> producer_ret(task_producer.size());
	std::vector<std::future<Ret>> consumer_ret(task_consumer.size());

	for (int i{}; i < producers.size(); ++i) {
		task_producer[i] = std::packaged_task<ProduSig>{producer};
		producer_ret[i] = task_producer[i].get_future();
		producers[i] = std::thread(std::move(task_producer[i]), 1000);
	}

	for (int i{}; i < consumers.size(); ++i) {
		task_consumer[i] = std::packaged_task<ConsuSig>{consumer};
		consumer_ret[i] = task_consumer[i].get_future();
		consumers[i] = std::thread(std::move(task_consumer[i]));
	}

	for (auto& x : producers) x.join();
	int produe_sum{};
	for (std::size_t i{}; i < producer_ret.size(); ++i) {
		auto [id, ret] = producer_ret[i].get();
		produe_sum += ret;
	}

	for (auto& x : consumers) x.join();
	int consume_sum{};
	for (std::size_t i{}; i < consumer_ret.size(); ++i) {
		auto [id, ret] = consumer_ret[i].get();
		consume_sum += ret;
		std::cout << id << " total consume " << ret << "\n";
	}
	std::cout << "\n";
	std::cout <<  "total consume " << consume_sum << "\n";
	std::cout <<  "total produce " << produe_sum << "\n";
	std::cout << "surplus " << s.size() << "\n";
	return 0;
}
