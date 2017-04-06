#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <iostream>
#include <ctime>

class EventLog
{
public:
	static bool init(std::ostream &outputStream = std::cout);
	static void log(const std::string msg, const std::string type = std::string("UNKNOWN"));
	EventLog(std::ostream &outputStream);
	void write(const std::string msg, const std::string type = std::string("UNKNOWN"));

private:
	static EventLog *singleton;
	static std::time_t timeInfo;
	static char timeToStrBuffer[100];
	std::ostream &outputStream;
	bool writeTime;
	bool writeType;
};

#endif // EVENTLOG_H
