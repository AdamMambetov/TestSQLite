#include <iostream>
#include <sqlite3.h>

int main()
{
    sqlite3* db;
    const char* dir = "test.db";
    int rc;

    rc = sqlite3_open(dir, &db);


    std::cout << rc << "\n";
}
