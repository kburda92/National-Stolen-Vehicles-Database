#pragma once
#include "Logger.h"
#include "DB.h"
#include "FieldBuilder.h"
class DatabaseLogger : public Logger
{
protected:
	void Write(ParametersMap& values) override
	{
		FieldBuilder builder(L"INSERT INTO vehicles_log");
		values[L"Date"] = GetCurrentDateTime();
		for (auto& value : values)
			builder.BuildPart(value.first, value.second);

		auto result = builder.GetResult();
		SQLite::Statement query(DB::GetInstance(), string(begin(result), end(result)));
		try
		{
			query.exec();
		}
		catch (SQLite::Exception& e)
		{
			//for our information
			wcout << e.what();
		}
	}
};