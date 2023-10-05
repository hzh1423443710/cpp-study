#include "logger.h"

#include <cstdarg>
#include <cstring>
#include <ctime>

// #include <iostream>

namespace hzh {
namespace utility {

Logger::~Logger() noexcept { this->close(); }

void Logger::open(const std::string& path) {
	if (m_writer.is_open()) {
		this->close();
	}
	m_writer.open(path, std::ios_base::app);
	if (m_writer.fail()) {
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) +
								 ": Exception: open log file failed, not found " + m_filename);
	}
	m_filename = path;
	m_len = m_writer.tellp();
}

void Logger::close() noexcept { m_writer.close(); }

bool Logger::log(Level level, const char* file, int line, const char* format, ...) {
	if (level < m_level) {
		return false;
	}
	if (!m_writer.is_open()) {
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) +
								 ": Exception: Unopened file");
	}

	// 写入文件
	va_list args_ptr;
	va_start(args_ptr, format);
	std::string content = makeBuffer(level, file, line, format, args_ptr);
	va_end(args_ptr);

	if (m_len + content.length() + strlen("\n") >= m_max) {
		this->rotate();
	}
	m_writer << content.c_str() << "\n";
	m_writer.flush();
	m_len += content.length();

	return true;
}

void Logger::setLevel(Level level) noexcept { m_level = level; }

bool Logger::logStderr(Level level, const char* file, int line, const char* format, ...) {
	if (level < m_level) {
		return false;
	}

	va_list args_ptr;
	va_start(args_ptr, format);
	std::string buff = makeBuffer(level, file, line, format, args_ptr);
	va_end(args_ptr);

	fprintf(stderr, "%s\n", buff.c_str());

	return true;
}

bool Logger::logStdout(Level level, const char* file, int line, const char* format, ...) {
	if (level < m_level) {
		return false;
	}
	va_list args_ptr;
	va_start(args_ptr, format);
	std::string buff = makeBuffer(level, file, line, format, args_ptr);
	va_end(args_ptr);
	fprintf(stdout, "%s\n", buff.c_str());

	return true;
}

std::string Logger::makeBuffer(Level level, const char* file, int line, const char* format,
							   va_list args_ptr) {
	// [time] [level] [file:line] msg
	const char* fmt = "[%s] [%s] [%s:%d] ";
	std::string cur_time = getCurtime();
	va_list args_ptr_cp;
	va_copy(args_ptr_cp, args_ptr);

	int len_prefix = snprintf(nullptr, 0, fmt, cur_time.c_str(), s_level_str[level], file, line);
	int len_msg = vsnprintf(nullptr, 0, format, args_ptr);

	// 拼接
	std::string buff(len_prefix + len_msg + 1, '\0');
	// prefix
	snprintf(buff.data(), buff.size(), fmt, cur_time.c_str(), s_level_str[level], file, line);
	// msg
	vsnprintf(buff.data() + len_prefix, buff.size() - len_prefix, format, args_ptr_cp);

	return buff;
}

void Logger::setMaxSize(size_t bytes) noexcept { m_max = bytes; }

void Logger::rotate() {
	// rename cur file
	std::string newname = m_filename + getCurtime(".%Y-%m-%d-%H:%M%S");
	if (0 != rename(m_filename.c_str(), newname.c_str())) {
		throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) +
								 ": Exception: rename log failed" + std::string(strerror(errno)));
	}
	// reopen new file
	this->close();
	this->open(m_filename);
}

std::string Logger::getCurtime(const char* fmt) {
	std::string cur_time(32, '\0');
	time_t t = time(nullptr);
	struct tm* ptm = localtime(&t);
	strftime(cur_time.data(), cur_time.size(), fmt, ptm);

	return cur_time;
}

}  // namespace utility
}  // namespace hzh