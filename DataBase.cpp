#include "DataBase.h"
#include "EmployeeInfo.h"
#include <sqlite3.h>
#include <iostream>
#include <algorithm>

DataBase::DataBase()
{
	sqlite3_open(FileDir, &db);
}

DataBase::~DataBase()
{
	sqlite3_close(db);
	db = nullptr;
}

void DataBase::CreateTable()
{
	if (!db) return;

	const char* sql = "CREATE TABLE IF NOT EXISTS EMPLOYEES("	\
		"ID         INTEGER PRIMARY KEY AUTOINCREMENT, "		\
		"NAME       TEXT NOT NULL, "							\
		"BIRTH_DATE TEXT NOT NULL, "							\
		"GENDER     TEXT NOT NULL);";
	try
	{
		int exit = 0;
		char* ErrorMsg;

		exit = sqlite3_exec(db, sql, nullptr, 0, &ErrorMsg);
		if (exit != SQLITE_OK)
		{
			std::cerr << "Error create table: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_free(ErrorMsg);
		}
		else
		{
			std::cout << "Table created" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
}

void DataBase::Insert(FEmployeeInfo Employee)
{
	if (!db) return;

	const char sql[] = "INSERT INTO EMPLOYEES (NAME,BIRTH_DATE,GENDER) VALUES (?,?,?);";
	sqlite3_stmt* stmt;

	sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, Employee.Name.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, Employee.GetBirthDate().c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, Employee.Gender.c_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		std::cerr << "Insert error: " << sqlite3_errmsg(db) << std::endl;
	}
	else
	{
		std::cout << "Insert successful" << std::endl;
	}
	sqlite3_finalize(stmt);
}

void DataBase::DisplayEmployers()
{
	if (!db) return;
	Employees.clear();

	const char* sql = "SELECT * FROM EMPLOYEES;";
	sqlite3_stmt* stmt;

	sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		int id = sqlite3_column_int(stmt, 0);
		const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* birth_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		const char* gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		Employees.push_back(FEmployeeInfo(id, name, birth_date, gender));
	}
	sqlite3_finalize(stmt);
	
	SortEmployeesByName();

	for (const auto& el : Employees)
	{
		std::cout << el.Name << '\t' << el.GetBirthDate() << '\t' << el.Gender << '\t' << el.GetYearsOld() << std::endl;
	}
}

void DataBase::SortEmployeesByName()
{
	std::sort(Employees.begin(), Employees.end(),
		[](const FEmployeeInfo& Employee1, const FEmployeeInfo& Employee2) -> bool {
			return Employee1.Name < Employee2.Name;
		});
}

int DataBase::DisplayCallback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
