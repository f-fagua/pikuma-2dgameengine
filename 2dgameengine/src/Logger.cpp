#include "Logger.h"
#include <iostream>
#include <time.h>
#include <ctime>

void Logger::Log(const std::string& message){
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "LOG | %d-%h-%G %T - ", timeinfo);

	std::cout << "\033[1;32m" << buffer << message << "\033[m" << std::endl;
}

void Logger::Err(const std::string& message){
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "ERR | %d-%h-%G %T - ", timeinfo);

	std::cout << "\033[1;31m" << buffer << message << "\033[m" << std::endl;
}