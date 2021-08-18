
#if !defined MY_FUNCTIONS_INCLUDE
#define MY_FUNCTIONS_INCLUDE

#include <string>

void copyFile(std::string fileNameLog, std::string tempFile, std::string fileContent);
void addNewData(std::string tempFile, std::string fileNameDb, std::string fileContent, std::string dayOfDigging, double weightOfGold, int buckets, std::string comment);
int* counters(std::string fileNameDb);

#endif

