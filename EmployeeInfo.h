#pragma once

#include <string>
#include <ctime>
#include "Constants.h"

struct FEmployeeInfo
{
	int ID;
	std::string Name;
	std::tm BirthDate;
	std::string Gender;

	const int INVALID_ID = -1;

	FEmployeeInfo()
	{
		this->ID = INVALID_ID;
		BirthDate = { 0 };
	}

	FEmployeeInfo(std::string Name, std::string BirthDate, std::string Gender)
	{
		this->ID = INVALID_ID;
		this->Name = Name;
		this->Gender = Gender;

		UpdateBirthDate(BirthDate);
	}

	FEmployeeInfo(int ID, std::string Name, std::string BirthDate, std::string Gender)
	{
		this->ID = ID;
		this->Name = Name;
		this->Gender = Gender;

		UpdateBirthDate(BirthDate);
	}

	FEmployeeInfo& operator=(const FEmployeeInfo& Employee)
	{
		this->ID = Employee.ID;
		this->Name = Employee.Name;
		this->BirthDate = Employee.BirthDate;
		this->Gender = Employee.Gender;

		return *this;
	}

	std::string GetBirthDate() const
	{
		char buffer[DATE_BUFFER_SIZE];
		strftime(buffer, DATE_BUFFER_SIZE, "%Y-%m-%d", &BirthDate);
		return buffer;
	}

	int GetYearsOld() const
	{
		const long DAY_IN_SEC = 86400L;
		const double YEAR_IN_DAYS = 365.0;
		std::tm NormalTm = BirthDate;
		time_t Normal = mktime(&NormalTm);
		time_t Current;

		time(&Current);
		return ((difftime(Current, Normal) + DAY_IN_SEC / 2) / DAY_IN_SEC) / YEAR_IN_DAYS;
	}

private:
	void UpdateBirthDate(const std::string& DateString)
	{
		BirthDate = { 0 };
		BirthDate.tm_year = atoi(DateString.substr(0, 4).c_str()) - 1900;
		BirthDate.tm_mon = atoi(DateString.substr(5, 2).c_str()) - 1;
		BirthDate.tm_mday = atoi(DateString.substr(8, 2).c_str());
	}
};
