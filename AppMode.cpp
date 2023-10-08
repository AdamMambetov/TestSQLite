#include "AppMode.h"

AppMode::AppMode()
{
	Mode = EAppMode::InitDB;
}

AppMode::AppMode(int Mode)
{
	if (!IsValidMode(Mode))
	{
		this->Mode = EAppMode::Invalid;
		return;
	}
	
	this->Mode = static_cast<EAppMode>(Mode);
}

AppMode::AppMode(std::string Mode)
{
	if (!IsNum(Mode))
	{ 
		this->Mode = EAppMode::Invalid;
		return;
	}

	const int ModeAsNum = atoi(Mode.c_str());

	if (!IsValidMode(ModeAsNum))
	{
		this->Mode = EAppMode::Invalid;
		return;
	}

	this->Mode = static_cast<EAppMode>(ModeAsNum);
}

int AppMode::GetArgCountByMode() const
{
	switch (Mode)
	{
	case EAppMode::Invalid:
		return ARG_COUNT_NOTHING;

	case EAppMode::InitDB:
		return ARG_COUNT_MODE_ONLY;

	case EAppMode::CreateEntry:
		return ARG_COUNT_MODE_AND_EMPLOYEE_INFO;

	case EAppMode::DisplayAllEntries:
		return ARG_COUNT_MODE_ONLY;
		
	default:
		return ARG_COUNT_MODE_ONLY;
	}
}

bool AppMode::IsNum(std::string str) const
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (!isdigit(str[i])) return false;
	}
	return true;
}

bool AppMode::IsValidMode(int Mode) const
{
	return Mode > 0 && Mode <= 6;
}
