
#if !defined MY_FUNCTIONS_INCLUDE
#define MY_FUNCTIONS_INCLUDE

#include <string>

int callback(void *NotUsed, int argc, char **argv, char **azColName);
int WriteToDataBase(std::string dateOfDigging, std::string weightOfGold, std::string buckets, std::string comment);
int getDataFromDB();

#endif

