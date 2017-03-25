#pragma once
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TestUtils.h"
#include "../Service/FilterBuilder.h"
#include "../Service/FieldBuilder.h"

using namespace std;

TEST_CASE("SelectWithoutFilter", "[FilterBuilder]") 
{
	FilterBuilder builder(L"select * from vehicles");
	auto expected = L"select * from vehicles";
	auto actual = builder.GetResult();
	REQUIRE(to_lower(expected) == to_lower(actual));
}

TEST_CASE("SelectWithOneFilter", "[FilterBuilder]")
{
	using namespace std;
	FilterBuilder builder(L"select * from vehicles");
	builder.BuildPart(L"registration", L"SPS20202");
	wstring expected = L"select * from vehicles "
					  "where registration = sps20202";
	auto actual = builder.GetResult();
	REQUIRE(to_lower(expected) == to_lower(actual));
}
TEST_CASE("SelectWithManyFilters", "[FilterBuilder]")
{
	using namespace std;
	FilterBuilder builder(L"select * from vehicles");
	builder.BuildPart(L"registration", L"WZW2020");
	builder.BuildPart(L"make", L"Chevrolet");
	builder.BuildPart(L"model", L"Camaro");

	wstring expected = L"select * from vehicles "
					  "where registration = WZW2020 "
					  "and make = Chevrolet "
					  "and model = Camaro";
	auto actual = builder.GetResult();
	REQUIRE(to_lower(expected) == to_lower(actual));
}

TEST_CASE("InsertWithoutFields", "[FieldBuilder]")
{
	FieldBuilder builder(L"insert into vehicles_log");
	auto expected = L"insert into vehicles_log";
	auto actual = builder.GetResult();
	REQUIRE(to_lower(expected) == to_lower(actual));
}

TEST_CASE("InsertWithOneField", "[FieldBuilder]")
{
	FieldBuilder builder(L"insert into vehicles_log");
	builder.BuildPart(L"registration", L"WZW2020");

	auto expected = L"insert into vehicles_log "
		"(registration) values (WZW2020)";
	auto actual = builder.GetResult();
	REQUIRE(to_lower(expected) == to_lower(actual));
}

TEST_CASE("InsertWithManyField", "[FieldBuilder]")
{
	FieldBuilder builder(L"insert into vehicles_log");
	builder.BuildPart(L"registration", L"WZW2020");
	builder.BuildPart(L"make", L"Chevrolet");
	builder.BuildPart(L"model", L"Camaro");

	auto expected = L"insert into vehicles_log "
		"(registration, make, model) "
		"values (WZW2020, Chevrolet, Camaro)";
	auto actual = builder.GetResult();
	REQUIRE(to_lower(expected) == to_lower(actual));
}