#pragma once
#include <string>
#include <algorithm>

using namespace std;

inline wstring to_lower(wstring str)
{
	transform(make_move_iterator(begin(str)), make_move_iterator(end(str)), begin(str), ::tolower);
	return move(str);
}