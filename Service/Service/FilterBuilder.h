#pragma once
#include "Builder.h"
#include <memory>

using namespace std;

class FilterBuilder : public Builder
{
public:
	FilterBuilder(wstring&& query) : result(move(query)) {};
	void BuildPart(wstring paramName, wstring paramValue)
	{
		result.append(first ? L" WHERE " : L" AND ");
		first = false;

		result.append(paramName + L" = '" + paramValue + L"'");
	}
	wstring GetResult() { return move(result); };
private:
	wstring result;
};

