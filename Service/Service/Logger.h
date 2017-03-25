#pragma once
#include <memory>
#include <string>
#include <map>

typedef std::map<std::wstring, std::wstring> ParametersMap;

class Logger
{
protected:
	std::shared_ptr<Logger> next;
	virtual void Write(ParametersMap& values) = 0;
public:
	void SetNext(std::shared_ptr<Logger> next)
	{
		this->next = next;
	}

	void Logger::Log(ParametersMap& values)
	{
		Write(values);
		if (next)
			next->Log(values);
	}
};