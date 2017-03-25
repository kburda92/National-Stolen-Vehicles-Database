#pragma once
#include <memory>

using namespace std;

class FilterBuilder
{
public:
	FilterBuilder(wstring&& query) : result(move(query)) {};
	void AddFilter(wstring paramName, wstring paramValue)
	{
		result.append(isFilterSet ? L" AND " : L" WHERE ");
		isFilterSet = true;

		result.append(paramName + L" = " + paramValue);
	}
	wstring GetResult() { return move(result); };
private:
	wstring result;
	bool isFilterSet = false;
};

