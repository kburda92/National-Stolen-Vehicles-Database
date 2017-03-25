#pragma once
#include <string>
class Builder
{
public:
	virtual std::wstring GetResult() = 0;
	virtual void BuildPart(std::wstring paramName, std::wstring paramValue) = 0;
protected:
	bool first = true;

};