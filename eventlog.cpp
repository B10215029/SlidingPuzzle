#include "eventlog.h"
#include <string>

EventLog *EventLog::singleton = NULL;
std::time_t EventLog::timeInfo = std::time(NULL);
char EventLog::timeToStrBuffer[100];

bool EventLog::init(std::ostream &outputStream)
{
	if (!singleton) {
		singleton = new EventLog(outputStream);
		return true;
	}
	else {
		return false;
	}
}

void EventLog::log(const std::string msg, const std::string type)
{
	if (singleton) {
		singleton->write(msg, type);
	}
}

EventLog::EventLog(std::ostream &outputStream): outputStream(outputStream), writeTime(true), writeType(true)
{

}

void EventLog::write(const std::string msg, const std::string type)
{
	if (writeType) {
		outputStream << "[" << type << "]";
	}
	if (writeTime) {
		timeInfo = std::time(NULL);
		std::strftime(timeToStrBuffer, sizeof(timeToStrBuffer), "%F %T", std::localtime(&timeInfo));
		outputStream << "[" << timeToStrBuffer << "]";
	}
	outputStream << msg << std::endl;
}
