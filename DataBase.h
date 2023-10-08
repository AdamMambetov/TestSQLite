#pragma once

#include <vector>

struct sqlite3;
struct FEmployeeInfo;

class DataBase
{
	sqlite3* db;
	const char* FileDir = "TEMP_DATABASE.db";

public:
	DataBase();
	~DataBase();
	
	std::vector<FEmployeeInfo> Employees;

	void CreateTable();

	void Insert(FEmployeeInfo Employee);

	void DisplayEmployers();

	void SortEmployeesByName();

protected:
	static int DisplayCallback(void* NotUsed, int argc, char** argv, char** azColName);
};
