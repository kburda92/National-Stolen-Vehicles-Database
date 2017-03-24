#include "SearchListener.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "FilterBuilder.h"
#include "DB.h"

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

SearchListener::SearchListener() : 
	listener(make_unique<http_listener>(L"http://localhost/NSVD/search"))
{
	listener->support(methods::GET, SearchForVehicle);
}

SearchListener::~SearchListener()
{}

void SearchListener::Run()
{
	listener->open()
		.then([uri = listener->uri().to_string()]() {wcout << "Listening at " << uri << '\n'; }) 
		.wait();
}

void SearchListener::SearchForVehicle(http_request& request)
{
	using namespace utility;
	using namespace utility::conversions;

	auto& searchParameters = uri::split_query(request.relative_uri().query());

	FilterBuilder builder("SELECT registration, make, model, owner FROM vehicles");
	for (auto& param : searchParameters)
		builder.AddFilter(to_utf8string(param.first), to_utf8string(param.second));

	SQLite::Statement query(DB::GetInstance(), builder.GetResult());

	json::value foundCars;
	int count = 0;
	while (query.executeStep())
	{
		json::value car;
		car[L"registration"] = json::value::string(to_string_t(query.getColumn(0).getString()));
		car[L"make"] = json::value::string(to_string_t(query.getColumn(1).getString()));
		car[L"model"] = json::value::string(to_string_t(query.getColumn(2).getString()));
		car[L"owner"] = json::value::string(to_string_t(query.getColumn(3).getString()));
		foundCars[count++] = car;
	}

	json::value searchResults;
	searchResults[L"status"] = json::value(L"success");
	searchResults[L"data"] = foundCars;

	status_code status;
	if (count)
		status = status_codes::OK;
	else
		status = status_codes::NotFound;
	request.reply(status, searchResults);
}