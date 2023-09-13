#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

// 读写锁 shared_mutex RAII: shared_lock<>

std::string resource("123456");
std::shared_mutex s_mtx;

void read() {
	std::shared_lock<std::shared_mutex> lock(s_mtx, std::try_to_lock);
	std::cout << std::this_thread::get_id() << " read: " << resource << "\n";
}
void write() {
	std::unique_lock<std::shared_mutex> lock(s_mtx);
	resource = "abcdefg";
	std::cout << std::this_thread::get_id() << " write ok\n";
}

int main(int argc, char* argv[]) {
	std::vector<std::thread> rts(5);
	std::thread wt;
	for (auto& x : rts) {
		x = std::thread(read);
	}
	wt = std::thread(write);

	for (auto& x : rts) {
		x.join();
	}
	wt.join();
	return 0;
}