#pragma once

#include <mutex>
#include <string>
#include <sstream>
#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#endif 

namespace LoggerIntern {

	enum LogColors {

		COL_BLACK		  = 0,   
		COL_BLUE		  = 1,
		COL_GREEN		  = 2,
		COL_CYAN		  = 3,
		COL_RED			  = 4,
		COL_MAGENTA		  = 5,
		COL_BROWN		  = 6,
		COL_LIGHTGRAY	  = 7,
		COL_DARKGRAY	  = 8,
		COL_LIGHTBLUE	  = 9,
		COL_LIGHTGREEN	  = 10,
		COL_LIGHTCYAN	  = 11,
		COL_LIGHTRED	  = 12,
		COL_LIGHTMAGENTA  = 13,
		COL_YELLOW		  = 14,
		COL_WHITE		  = 15
	};
}

#define FILENAME			(std::filesystem::path(__FILE__).filename().string())

#define LOGERROR(...)	  { Logger(false, "ERROR", LoggerIntern::COL_LIGHTRED, FILENAME, __LINE__, __VA_ARGS__); \
							Logger(true, "ERROR", LoggerIntern::COL_LIGHTRED, FILENAME, __LINE__, __VA_ARGS__); \
							__debugbreak(); }

#define LOGWARN(...)		Logger(false, "WARN", LoggerIntern::COL_YELLOW, FILENAME, __LINE__, __VA_ARGS__);

#define LOG(...)			Logger(false, "INFO", LoggerIntern::COL_CYAN, FILENAME, __LINE__, __VA_ARGS__);

#define LOGINFO(txt, ...)	Logger(false, txt, LoggerIntern::COL_WHITE, FILENAME, __LINE__, __VA_ARGS__);	

class Logger {
public:
	template<typename... Args>
	Logger(bool LogToFile, const std::string& pLogInfoDescription, int color, const std::string& file, int line, const Args& ... args) :
		m_LogToFile(LogToFile),
		m_LogInfoDescription(pLogInfoDescription),
		m_File(file),
		m_Line(line)
#ifdef _WIN32
		, m_Color((WORD)color)
#endif 
	{
		std::ostringstream msg;
		Log(msg, args...);
	}

private:
	template<class T, typename... Args>
	void Log(std::ostringstream& msg, T value, const Args& ... args)
	{
		msg << ' ' << value;
		Log(msg, args...);
	}

	void Log(std::ostringstream& msg);

public:
	static std::string m_logFilePath;

private:

#ifdef _WIN32
	WORD m_Color;
#endif 

	const std::string& m_LogInfoDescription;
	const std::string& m_File;
	
	int m_Line;

	bool m_LogToFile = false;

	static std::mutex m_Mutex;
};