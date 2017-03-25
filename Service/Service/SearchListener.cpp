#include "SearchListener.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "FilterBuilder.h"
#include "DB.h"
#include "ConsoleLogger.h"
#include "DatabaseLogger.h"

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

SearchListener::SearchListener() : 
	listener(make_unique<http_listener>(L"http://localhost/NSVD/search")),
	consoleLogger(make_shared<ConsoleLogger>()),
	databaseLogger(make_shared<DatabaseLogger>())
{
	listener->support(methods::GET, SearchForVehicle);
	//chain of resposibility pattern - consoleLogger will automatically pass the data to database logger
	consoleLogger->SetNext(databaseLogger);
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

	FilterBuilder builder(L"SELECT registration, make, model, owner FROM vehicles");
	for (auto& param : searchParameters)
		builder.AddFilter(param.first, param.second);

	auto result = builder.GetResult();
	SQLite::Statement query(DB::GetInstance(), string(begin(result), end(result)));

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