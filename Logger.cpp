#include "Logger.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::mutex Logger::m_Mutex;
std::string Logger::m_logFilePath = "log.txt";

void indent(std::ostringstream& of, int s, int e) {
	for (int i = s; i < e; i++)
		of << " ";
}

void Logger::Log(std::ostringstream & msg)
{
	std::ostringstream of;

	of << " [ " << m_LogInfoDescription;

	indent(of, (int)m_LogInfoDescription.size(), 10);

	of << "] [ " << m_File;

	indent(of, (int)m_File.size(), 20);

	of << " : ( line : " << m_Line;

	int s = 0;
	while (m_Line /= 10) s++;

	indent(of, s, 5);

	of << ") ] : " << msg.str();

	m_Mutex.lock();

	if (!m_LogToFile)
#ifdef _WIN32
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, m_Color);
		std::cout << of.str() << std::endl;
		SetConsoleTextAttribute(h, (WORD)LoggerIntern::COL_WHITE);
	}
#else
		std::cout << of.str() << std::endl;
#endif 
	else {
		std::ofstream f(Logger::m_logFilePath, std::ios::app);

		if (!f.good())
			return;

		f << of.str() << "\n";
		f.close();
	}

	m_Mutex.unlock();
}
