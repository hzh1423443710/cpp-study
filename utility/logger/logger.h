#pragma once

#include <fstream>
#include <string>

namespace hzh {
namespace utility {

// 命名空间前缀
#define NAMESPACE_PREFIX hzh::utility

// ##__VA_ARGS__ 允许可变参数为空
#define DEBUG(fmt, ...)                                                                     \
	NAMESPACE_PREFIX::Logger::getInstance()->log(NAMESPACE_PREFIX::Logger::DEBUG, __FILE__, \
												 __LINE__, fmt, ##__VA_ARGS__)

#define INFO(fmt, ...)                                                                     \
	NAMESPACE_PREFIX::Logger::getInstance()->log(NAMESPACE_PREFIX::Logger::INFO, __FILE__, \
												 __LINE__, fmt, ##__VA_ARGS__)

#define WARNING(fmt, ...)                                                                     \
	NAMESPACE_PREFIX::Logger::getInstance()->log(NAMESPACE_PREFIX::Logger::WARNING, __FILE__, \
												 __LINE__, fmt, ##__VA_ARGS__)

#define ERROR(fmt, ...)                                                                     \
	NAMESPACE_PREFIX::Logger::getInstance()->log(NAMESPACE_PREFIX::Logger::ERROR, __FILE__, \
												 __LINE__, fmt, ##__VA_ARGS__)

#define FATAL(fmt, ...)                                                                     \
	NAMESPACE_PREFIX::Logger::getInstance()->log(NAMESPACE_PREFIX::Logger::FATAL, __FILE__, \
												 __LINE__, fmt, ##__VA_ARGS__)

#define LOG_STDERR(level, fmt, ...)                                                    \
	NAMESPACE_PREFIX::Logger::getInstance()->logStderr(level, __FILE__, __LINE__, fmt, \
													   ##__VA_ARGS__)

#define LOG_STDOUT(level, fmt, ...)                                                    \
	NAMESPACE_PREFIX::Logger::getInstance()->logStdout(level, __FILE__, __LINE__, fmt, \
													   ##__VA_ARGS__)

class Logger {
public:
	enum Level { DEBUG, INFO, WARNING, ERROR, FATAL, LEVEL_COUNT };
	static constexpr const char* s_level_str[LEVEL_COUNT] = {"DEBUG", "INFO", "WARNING", "ERROR",
															 "FATAL"};

public:
	~Logger() noexcept;
	static Logger* getInstance() {
		static Logger logger;
		return &logger;
	}
	// 输出到文件
	bool log(Level level, const char* file, int line, const char* format, ...);
	// 输出到标准错误
	bool logStderr(Level level, const char* file, int line, const char* format, ...);
	// 输出到标准输出
	bool logStdout(Level level, const char* file, int line, const char* format, ...);
	// 设置单个文件大小上限
	void setMaxSize(size_t bytes) noexcept;
	void rotate();
	void setLevel(Level level) noexcept;
	void open(const std::string& path);
	void close() noexcept;

private:
	Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger& other) = delete;
	static std::string getCurtime(const char* fmt = "%Y/%m/%d-%H:%M:%S");
	static std::string makeBuffer(Level level, const char* file, int line, const char* format,
								  va_list args_ptr);

private:
	std::ofstream m_writer;
	std::string m_filename;
	Level m_level = DEBUG;
	size_t m_max = 1 * 1024 * 1024;
	size_t m_len{};
};

}  // namespace utility
}  // namespace hzh