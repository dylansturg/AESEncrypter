#pragma once

#include "stdafx.h"

#include <string>

using namespace std;

class Logger{
public:
	static void SetupLogging(string filename);
	static void LogEntry(string action, string message);

	static void DisableLogging();
	static void EnableLogging();

private:
	static bool LoggingEnabled;
	static string filename;

};