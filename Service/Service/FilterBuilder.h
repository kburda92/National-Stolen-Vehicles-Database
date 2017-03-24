#pragma once
#include <memory>

using namespace std;

class FilterBuilder
{
public:
	FilterBuilder(string&& query = "") : result(move(query)) {};
	void BuildPart(string paramName, string paramValue)
	{
		result.append(isFilterSet ? " AND" : " WHERE ");
		isFilterSet = true;

		result.append(paramName + "=" + paramValue);
	}
	string GetResult() { return move(result); };
private:
	string result;
	bool isFilterSet = false;
};

