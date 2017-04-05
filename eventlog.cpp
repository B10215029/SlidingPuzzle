#include "eventlog.h"
#include <ctime>
#include <iostream>

EventLog::EventLog()
{
	write("EventLog::EventLog()");
	print();
}

void EventLog::write(string msg, bool use_time)
{
	time_t t = time(0);
	struct tm *now = localtime(& t);
	log << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << " "
		<< now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " "
		<< msg << endl;
}

bool EventLog::save(string path, string file_name)
{

}

bool EventLog::save()
{

}

bool EventLog::print()
{
	cout << log.str();
}
