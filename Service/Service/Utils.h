#pragma once
#include <boost\date_time\posix_time\posix_time.hpp>

std::wstring GetCurrentDateTime()
{
	return boost::posix_time::to_simple_wstring(boost::posix_time::second_clock::universal_time());
}
