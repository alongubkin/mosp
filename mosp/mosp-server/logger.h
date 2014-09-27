#ifndef _H_LOGGER
#define _H_LOGGER

#include <iostream>
#include <string>
#include <cstdarg>

#define LOG_PRINT(message, ...) printf(message, ##__VA_ARGS__)

class Logger
{
public:
	template<class... Args>
	static void Error(const char* format, Args&&... args)
	{
		std::string buff(format);
		buff.append("\n");
		std::string _res("ERROR: ");
		_res.append(buff);

		printf(_res.c_str(), std::forward<Args>(args)...);
	}

	template<class... Args>
	static void Info(const char* format, Args&&... args)
	{
		std::string buff(format);
		buff.append("\n");
		std::string _res("INFO: ");
		_res.append(buff);

		printf(_res.c_str(), std::forward<Args>(args)...);
	}
};

#endif