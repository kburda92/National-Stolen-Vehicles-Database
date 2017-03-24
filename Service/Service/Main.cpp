#include <iostream>
#include <fstream>
#include <string>
#include "DB.h"
#include "SearchListener.h"

using namespace std;

bool CreateTables()
{
	auto& db = DB::GetInstance();
	int tables = db.execAndGet("SELECT COUNT(*) FROM sqlite_master "
		"WHERE type = 'table' "
		"AND (Name = 'Vehicles' "
		"OR Name = 'Vehicles_Log')");

	if (tables == 2)
		return true;

	ifstream scriptFile;
	try
	{
		scriptFile.open("script.sql");
		string script((istreambuf_iterator<char>(scriptFile)), istreambuf_iterator<char>());
		scriptFile.close();
		try
		{
			db.exec(script);
		}
		catch (SQLite::Exception& e)
		{
			wcout << e.what();
			return false;
		}
	}
	catch (const ifstream::failure& e)
	{
		wcout << e.what();
		scriptFile.close();
		return false;
	}
	return true;
}

int main()
{
	if(!CreateTables())
		return -1;

	SearchListener listener;
	//we have only one listener, so we don't need to run it in separate threads
	try
	{
		listener.Run();
		while (1);
	}
	catch (exception const & e)
	{
		wcout << e.what() << endl;
	}

	return 0;
}