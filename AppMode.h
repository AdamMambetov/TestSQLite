#pragma once

#include <string>

enum class EAppMode : unsigned __int8
{
	Invalid					= 0,
	InitDB					= 1,
	CreateEntry				= 2,
	DisplayAllEntries		= 3,
	AutoFillEntries			= 4,
	DisplayTimeByCriterion	= 5,
	OptimizeDB				= 6,
};

class AppMode
{
	EAppMode Mode;

public:
	AppMode();
	AppMode(int Mode);
	AppMode(std::string Mode);

	EAppMode GetMode() const { return Mode; }
	int GetModeAsInt() const { return static_cast<int>(Mode); }
	void SetMode(EAppMode Mode) { this->Mode = Mode; }
	void SetMode(int Mode) { this->Mode = static_cast<EAppMode>(Mode); }

	int GetArgCountByMode() const;

	const int ARG_COUNT_NOTHING = 1;
	const int ARG_COUNT_MODE_ONLY = 2;
	const int ARG_COUNT_MODE_AND_EMPLOYEE_INFO = 5;

private:
	bool IsNum(std::string str) const;
	bool IsValidMode(int Mode) const;
};
