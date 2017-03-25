#pragma once
#include "config.h"
#include "../Service/ConsoleLogger.h"

using namespace std;

TEST_CASE("LogWithParameters", "[ConsoleLogger]")
{
	ostringstream os;
	unique_ptr<Logger> logger = make_unique<ConsoleLogger>(os);
	parameters_map params;
	params[L"registration"] = L"ABCDEFG";
	params[L"owner"] = L"John Walt";
	logger->Log(params);
	auto expected = "Searching for: ";
	auto actual = os.str();
	REQUIRE(expected == actual);
}