#include "log.hpp"

#ifndef NDEBUG
	#include <ctime>
	#include <chrono>
	#include <fstream>
	#include <fstream>
#endif

void skgl::log(const std::string& msg)
{
#ifndef NDEBUG
	static std::ofstream out("skgl.log", std::ios_base::app);

	auto t = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t(t);

	out << std::ctime(&tt) << " " << msg << "\n\n";
#endif
}