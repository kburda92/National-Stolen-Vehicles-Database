#pragma once
#include <memory>

namespace web { namespace http { 
	class http_request;
namespace experimental {namespace listener {
	class http_listener;
}}}};

class SearchListener
{
public:
	SearchListener();
	~SearchListener();
	void Run();
private:
	std::unique_ptr<web::http::experimental::listener::http_listener> listener;
	static void SearchForVehicle(web::http::http_request& request);
};

