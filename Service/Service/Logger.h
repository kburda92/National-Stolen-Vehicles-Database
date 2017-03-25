#pragma once
#include<memory>
#include <cpprest/http_listener.h>

using namespace std;

class Logger
{
protected:
	shared_ptr<Logger> next;
	virtual void Write(map<utility::string_t, utility::string_t>& values) = 0;
public:
	void SetNext(shared_ptr<Logger> next)
	{
		this->next = next;
	}

	virtual void Log(map<utility::string_t, utility::string_t>& values)
	{
		Write(values);
		if (next)
			next->Log(values);
	}
};

class ConsoleLogger : public Logger
{
protected:
	void Write(map<utility::string_t, utility::string_t>& values)
	{
		//TODO - save to console
	}
};

class DatabaseLogger : public Logger
{
protected:
	void Write(map<utility::string_t, utility::string_t>& values)
	{
		//TODO - save to db

	}
};