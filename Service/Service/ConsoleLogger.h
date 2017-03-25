#pragma once
#include "Logger.h"
#include <iostream>
#include "Utils.h"

class ConsoleLogger : public Logger
{
private:
	std::wostream& os;
public:
	ConsoleLogger(std::wostream& os = std::wcout) : os(os) {}
protected:
	virtual void Write(ParametersMap& values) override
	{
		os << GetCurrentDateTimeStream() << " Search parameters:";
		for (auto& value : values)
			os << " " << value.first << ": " << value.second;
	}
};