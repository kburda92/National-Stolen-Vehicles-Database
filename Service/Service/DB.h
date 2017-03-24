#include "SQLiteCpp\SQLiteCpp.h"

using namespace SQLite;

class DB
{
public:
	static Database& GetInstance()
	{
		static Database db("NSVD.db", OPEN_READWRITE | OPEN_CREATE);
		return db;
	}
};