#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

class SpinLock {
public:
	SpinLock() : flag(ATOMIC_FLAG_INIT) {}
	void lock() {
		while (flag.test_and_set()) {
		}
	}
	void unlock() { flag.clear(); }

private:
	std::atomic_flag flag;
};

// 初始化为false
std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;
int g_n;
// 自旋锁
SpinLock spin;

void test_spin_lock();
void test_atomic_flag();

int main(int argc, char* argv[]) {
	test_spin_lock();
    // test_atomic_flag();

	return 0;
}

void test_atomic_flag() {
	std::vector<std::thread> ts(2);
	for (auto& x : ts) {
		x = std::thread([]() {
			for (int i{}; i < 1000000; ++i) {
				// 设为true, 返回先前值
				while (spin_lock.test_and_set()) std::cout << std::this_thread::get_id() << " ";
				g_n++;
				spin_lock.clear();	// 修改为false
			}
		});
	}
	for (auto& x : ts) x.join();
	std::cout << "\ng_n = " << g_n << "\n";
}

void test_spin_lock() {
	std::vector<std::thread> ts(2);
	for (auto& x : ts) {
		x = std::thread([]() {
			for (int i{}; i < 10000000; ++i) {
				spin.lock();
				g_n++;
				spin.unlock();
			}
		});
	}
	for (auto& x : ts) x.join();
	std::cout << "g_n = " << g_n << "\n";
}
