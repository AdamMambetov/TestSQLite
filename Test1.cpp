#include <iostream>
#include "Constants.h"
#include "DataBase.h"
#include "AppMode.h"
#include "EmployeeInfo.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cerr << "App mode not specified!" << std::endl;
        return 0;
    }

    AppMode CurrentAppMode(argv[1]);
    DataBase* DB = new DataBase();

    switch (CurrentAppMode.GetMode())
    {
    case EAppMode::Invalid:
        std::cerr << "App mode are invalid!" << std::endl;
        break;

    case EAppMode::InitDB:
        if (argc != CurrentAppMode.GetArgCountByMode())
        {
            std::cerr << "Wrong number of arguments!" << std::endl;
            break;
        }

        DB->CreateTable();
        break;

    case EAppMode::CreateEntry:
        if (argc != CurrentAppMode.GetArgCountByMode())
        {
            std::cerr << "Wrong number of arguments!" << std::endl;
            break;
        }

        DB->Insert(FEmployeeInfo(argv[2], argv[3], argv[4]));
        break;

    case EAppMode::DisplayAllEntries:
        if (argc != CurrentAppMode.GetArgCountByMode())
        {
            std::cerr << "Wrong number of arguments!" << std::endl;
            break;
        }

        DB->DisplayEmployers();
        break;

    default:
        std::cerr << "This app mode does not work!" << std::endl;
        break;
    }
    return 0;
}
