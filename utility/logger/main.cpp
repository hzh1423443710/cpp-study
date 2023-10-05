#include "logger.h"
#include <iostream>

int main(int argc, char* argv[]) {
	using namespace hzh::utility;
	try {
		Logger::getInstance()->open("test.log");
		Logger::getInstance()->setLevel(Logger::INFO);
		Logger::getInstance()->log(Logger::Level::DEBUG, __FILE__, __LINE__,
								   "My nams is %s, i'm %d years old", "hzh", 21);
		DEBUG("This is %s, %d", Logger::s_level_str[Logger::DEBUG], Logger::DEBUG);
		INFO("This is %s, %d", Logger::s_level_str[Logger::INFO], Logger::INFO);
		WARNING("This is %s, %d", Logger::s_level_str[Logger::WARNING], Logger::WARNING);
		ERROR("This is %s, %d", Logger::s_level_str[Logger::ERROR], Logger::ERROR);
		FATAL("This is %s, %d", Logger::s_level_str[Logger::FATAL], Logger::FATAL);

		LOG_STDERR(Logger::DEBUG, "This will output to stderr\n");
		LOG_STDOUT(Logger::DEBUG, "This will output to stdout\n");

	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}