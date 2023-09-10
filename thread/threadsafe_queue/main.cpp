#include <algorithm>
#include <iostream>
#include <random>

#include "threadsafe_queue.hpp"

class Simulate {
public:
	Simulate() = default;
	void producer() {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(1, 100);
		int n = NUM;
		while (n--) {
			int val_in = uni(rng);
			que.push(val_in);
			// printf("%d, produce [%d]\n", std::this_thread::get_id(), val_in);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::cout << std::this_thread::get_id() << ", total produce " << NUM << "\n";
	}
	void consumer() {
		int cnt{};
		while (!que.empty()) {
			int ret;
			que.wait_pop(ret);
			// printf("  %d, consume [%d]\n", std::this_thread::get_id(), ret);
			cnt++;
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::this_thread::get_id() << ", total consume " << cnt << "\n";
	}

	auto size() const { return que.size(); }

private:
	threadsafe_queue<int> que;
	constexpr static int NUM = 200;
};

int main(int argc, char* argv[]) {
	std::thread producer;
	std::vector<std::thread> consumers(5);

	Simulate s;
	producer = std::thread(&Simulate::producer, &s);
	// getchar();
	std::this_thread::sleep_for(std::chrono::milliseconds{100});
	for (auto& x : consumers) {
		x = std::thread(&Simulate::consumer, &s);
	}

	producer.join();
	std::for_each(consumers.begin(), consumers.end(), std::mem_fn(&std::thread::join));
	std::cout << "Surplus products = " << s.size() << "\n";

	return 0;
}