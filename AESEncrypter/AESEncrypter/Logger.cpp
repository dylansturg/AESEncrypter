#include "stdafx.h"

#include "Logger.h"
#include <fstream>

bool Logger::LoggingEnabled = false;
string Logger::filename = "";

void Logger::SetupLogging(string filename)
{
	Logger::LoggingEnabled = true;
	Logger::filename = filename;

	fstream log(filename, ios::out | ios::trunc);
	log.close();
}

void Logger::LogEntry(string action, string message)
{
	if (Logger::LoggingEnabled)
	{
		fstream log(Logger::filename, ios::out | ios::app);
		log << action;
		log << ": ";
		log << message;
		log.close();
	}
}

void Logger::EnableLogging()
{
	Logger::LoggingEnabled = true;
}

void Logger::DisableLogging()
{
	Logger::LoggingEnabled = false;
}