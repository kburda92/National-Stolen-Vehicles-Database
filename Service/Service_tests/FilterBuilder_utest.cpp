#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Service/FilterBuilder.h"

TEST_CASE("SelectWithoutFilter", "[FilterBuilder]") 
{
	FilterBuilder builder("select * from vehicles");
	auto expected = "select * from vehicles";
	auto actual = builder.GetResult();
	REQUIRE(expected == actual);
}

TEST_CASE("SelectWithOneFilter", "[FilterBuilder]")
{
	using namespace std;
	FilterBuilder builder("select * from vehicles");
	builder.AddFilter("registration", "SPS20202");
	string expected = "select * from vehicles "
					  "where registration = sps20202";
	auto actual = builder.GetResult();
	transform(begin(expected), end(expected), begin(expected), ::tolower);
	transform(begin(actual), end(actual), begin(actual), ::tolower);
	REQUIRE(expected == actual);
}
TEST_CASE("SelectWithManyFilters", "[FilterBuilder]")
{
	using namespace std;
	FilterBuilder builder("select * from vehicles");
	builder.AddFilter("registration", "WZW2020");
	builder.AddFilter("make", "Chevrolet");
	builder.AddFilter("model", "Camaro");

	string expected = "select * from vehicles "
					  "where registration = WZW2020 "
					  "and make = Chevrolet "
					  "and model = Camaro";
	auto actual = builder.GetResult();
	transform(begin(expected), end(expected), begin(expected), ::tolower);
	transform(begin(actual), end(actual), begin(actual), ::tolower);
	REQUIRE(expected == actual);
}

