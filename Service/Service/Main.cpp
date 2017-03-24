#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void SearchForVehicle(http_request request)
{
	//TODO - search for vehicle in database;
}

int main()
{
	http_listener listener{ L"http://localhost/NSVD/search" };
	listener.support(methods::GET, SearchForVehicle);

	//we have only one listener, so we don't need to run it in separate threads
	listener.open()
		.then([&listener]() {std::wcout << "Listening at " << listener.uri().to_string() << '\n'; })
		.wait();
	while (1);


	return 0;
}