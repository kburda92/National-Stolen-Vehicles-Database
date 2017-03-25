#pragma once
#include "catch.hpp"
#include "TestUtils.h"
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

	//We get actual log and cut data
	auto actual = os.str();
	actual = std::wstring(begin(actual) + 21, end(actual));

	wstring expected = L"Search parameters: owner: John Walt registration: ABCDEFG";
	REQUIRE(to_lower(actual) == to_lower(expected));
}