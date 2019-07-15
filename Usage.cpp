
#include "Logger.h"

void main() {

	const char* line = "line";

	LOG("This", "is", "in", 1, line); 

	LOGERROR("This gets logged to the Console and to File and execution breaks");

	LOGWARN("This is yellow :)");

	int i = 0;
	char c = 'c';
	std::string s = "Hello Wold!";

	LOG(i, c, s);

	// Output
	// [ INFO      ] [ Usage.cpp            : ( line : 8     ) ] :  This is in 1 line
	// [ ERROR     ] [ Usage.cpp            : ( line : 10    ) ] :  This gets logged to the Console and to File and execution breaks
	// [ WARN      ] [ Usage.cpp            : ( line : 12    ) ] :  This is yellow :)
	// [ INFO      ] [ Usage.cpp            : ( line : 18    ) ] :  0 c Hello Wold!
}
