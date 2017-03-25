#pragma once
#include "Builder.h"
#include <memory>
#include <string>

using namespace std;

class FieldBuilder : public Builder
{
public:
	FieldBuilder(wstring&& query) : resultNames(move(query)) {};
	void BuildPart(wstring paramName, wstring paramValue)
	{
		resultNames.append(first ? L" (" : L", ");
		resultValues.append(first ? L") VALUES ('" : L"', '");

		first = false;

		resultNames.append(paramName);
		resultValues.append(paramValue);
	}
	wstring GetResult() { return move(resultNames + resultValues + (resultValues.empty() ? L"" : L"')")); };
private:
	wstring resultNames, resultValues;
};
