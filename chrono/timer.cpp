#include <iostream>
#include <chrono>
#include <thread>

//计时
class Timer
{
public:
	Timer() :m_duration()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		m_duration = std::chrono::high_resolution_clock::now() - m_startTime;
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(m_duration).count() << "ms" << std::endl;//转换成毫秒
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
	std::chrono::nanoseconds m_duration;
};

int main()
{
	using namespace std::chrono_literals;
	//方式1
	auto time_start = std::chrono::high_resolution_clock::now();

	std::this_thread::sleep_for(1s);

	auto time_end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> interval = time_end - time_start;
	std::cout << interval.count() << "s" << std::endl;

	//方式2 借助对象的声明周期
	{
		Timer time;
		for (int i = 0; i < 100; i++) {		//打印100次
			std::cout << "Hello Chrono!" << std::endl;
			//std::cout << "Hello Chrono!\n";//更快
		}
	}

	return 0;
}
