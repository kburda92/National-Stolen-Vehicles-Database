#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Service/FilterBuilder.h"

TEST_CASE("SelectWithoutFilter", "[FilterBuilder]") 
{
	FilterBuilder builder(L"select * from vehicles");
	auto expected = L"select * from vehicles";
	auto actual = builder.GetResult();
	REQUIRE(expected == actual);
}

TEST_CASE("SelectWithOneFilter", "[FilterBuilder]")
{
	using namespace std;
	FilterBuilder builder(L"select * from vehicles");
	builder.AddFilter(L"registration", L"SPS20202");
	wstring expected = L"select * from vehicles "
					  "where registration = sps20202";
	auto actual = builder.GetResult();
	transform(begin(expected), end(expected), begin(expected), ::tolower);
	transform(begin(actual), end(actual), begin(actual), ::tolower);
	REQUIRE(expected == actual);
}
TEST_CASE("SelectWithManyFilters", "[FilterBuilder]")
{
	using namespace std;
	FilterBuilder builder(L"select * from vehicles");
	builder.AddFilter(L"registration", L"WZW2020");
	builder.AddFilter(L"make", L"Chevrolet");
	builder.AddFilter(L"model", L"Camaro");

	wstring expected = L"select * from vehicles "
					  "where registration = WZW2020 "
					  "and make = Chevrolet "
					  "and model = Camaro";
	auto actual = builder.GetResult();
	transform(begin(expected), end(expected), begin(expected), ::tolower);
	transform(begin(actual), end(actual), begin(actual), ::tolower);
	REQUIRE(expected == actual);
}

