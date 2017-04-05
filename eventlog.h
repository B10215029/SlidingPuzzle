#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <sstream>

using namespace std;

class EventLog
{
public:
	EventLog();
	void write(string msg, bool use_time=true);
	bool save(string path, string file_name);
	bool save(); // default path and name
	bool print(); // print to screen

private:
	stringstream log;
};

#endif // EVENTLOG_H
