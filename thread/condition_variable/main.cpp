#include <condition_variable>
#include <iostream>
#include <thread>

// 理解条件变量
std::condition_variable cond;
std::mutex mtx;

// 情况一 无谓词
void cond_case1() {
	std::thread t1([]() {
		std::unique_lock<std::mutex> lk(mtx);
		std::cout << "son thread get mutex\n";
		//  阻塞并让出锁
		cond.wait(lk);
		//  被唤醒 解除阻塞 获取锁
		std::cout << "Completed\n";
	});
	std::this_thread::sleep_for(std::chrono::milliseconds{1});
	{
		std::unique_lock<std::mutex> lk(mtx);
		std::cout << "main thread get mutex\n";
		getchar();
		cond.notify_one();
		std::cout << "notify ok\n";
		getchar();	// 释放锁
	}
	t1.join();
}

// 情况2 有谓词
void cond_case2() {
	bool pred = false;
	std::thread t1([&pred]() {
		std::unique_lock<std::mutex> lk(mtx);
		std::cout << "son thread get mutex\n";
#if 0
		while (!pred) {	    // 先判断谓词
			std::cout << "wait...\n";
			cond.wait(lk);	// 阻塞并解锁 等待唤醒
			std::cout << "receive notify\n";
		}
#else
		// 等价于
		cond.wait(lk, [&pred]() { return pred; });
#endif
		std::cout << "Completed\n";
	});

	std::this_thread::sleep_for(std::chrono::milliseconds{1});
	{
		std::unique_lock<std::mutex> lk(mtx);
		std::cout << "main thread get mutex\n";
		getchar();
		cond.notify_one();
		std::cout << "notify ok\n";
	}
	getchar();
	pred = true;
	cond.notify_one();
	t1.join();
}

int main(int argc, char* argv[]) {
	// cond_case1();
	cond_case2();
	return 0;
}
