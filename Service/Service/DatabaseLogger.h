#pragma once
#include "Logger.h"
#include "DB.h"
#include "FilterBuilder.h"
class DatabaseLogger : public Logger
{
protected:
	void Write(ParametersMap& values) override
	{
		FilterBuilder builder(L"INSERT INTO vehicles_log");
	}
};