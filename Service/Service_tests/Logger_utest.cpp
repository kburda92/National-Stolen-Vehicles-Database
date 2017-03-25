#pragma once
#include "catch.hpp"
#include "../Service/ConsoleLogger.h"

using namespace std;

TEST_CASE("LogWithParameters", "[ConsoleLogger]")
{
	using namespace std;
	wostringstream os;
	auto logger = make_shared<ConsoleLogger>(os);
	ParametersMap params;
	params[L"registration"] = L"ABCDEFG";
	params[L"owner"] = L"John Walt";
	logger->Log(params);

	auto actual = os.str();
	//We check actual log without data with small letters 
	actual = std::wstring(begin(actual) + 21, end(actual));
	transform(begin(actual), end(actual), begin(actual), ::tolower);

	wstring expected = L"Search parameters: owner: John Walt registration: ABCDEFG";
	transform(begin(expected), end(expected), begin(expected), ::tolower);

	REQUIRE(actual == expected);
	//REQUIRE(actual.find(L"Searching for: ") != std::wstring::npos);
	//REQUIRE(actual.find(L"registration: ABCDEFG") != std::wstring::npos);
	//REQUIRE(actual.find(L"owner: John Walt") != std::wstring::npos);

}