
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "sqlite3.h"
#include "myfunctions.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ofstream;
using std::stoi;

int main() {
    string exitProgram;
    
    cout <<"      _____           _       _ "<< endl;
    cout <<"     / ____|         | |     | | "<< endl;
    cout <<"    | |  __    ___   | |    _| | "<< endl;
    cout <<"    | | |_ |  / _ \\  | |  / _` | "<< endl;
    cout <<"    | |__| | | (_) | | | | (_| | "<< endl;
    cout <<"     \\_____|  \\___/  |_|  \\__,_| "<< endl;
                         
    while (exitProgram!="q") {
        double totalWeight;
        string fileNameLog("GoldLog.txt");
        fstream fileoutLog;
        int buckets;
        string dayOfDigging;
        string fileNameDb("DataBase.txt");
        fstream fileoutDb;
        string fileContent;
        int sizeOfFile;
        string concatContent;
        int wordCounter = 0;
        double totalWeightOfGold = 0;
        int totalBuckets = 0;
        string tempFile("tempG.txt");
        char oldFile[] = "GoldLog.txt";
        char newFile[] = "tempG.txt";
        ofstream fileoutTemp;
        int timesWentThere = 0;
        string comment = "No comment.";
        double bucketsPerGram = 0;
        string nothing;

        //promting user for data
        cout << "\nEnter gold finding Date(DD.MM.YYYY): ";
        cin >> dayOfDigging;

        cout << "\nEnter weight of Flasque: ";
        cin >> totalWeight;
        cout << "\n";
        cout << "\nEnter bucket count: ";
        cin >> buckets;
        cout << "\nAdd a comment: ";
        getline(cin, nothing);
        getline(cin, comment);
        double weightOfGold = (totalWeight - 10.14)*1000;
        
        copyFile(fileNameLog, tempFile, fileContent);

        addNewData(tempFile, fileNameDb, fileContent, dayOfDigging, weightOfGold, buckets, comment);

        int* count = counters(fileNameDb);
        
        //writes the statistics to the GoldLog file.
        fileoutTemp.open(tempFile, std::ios_base::app);
        if (!fileoutTemp.is_open()) {
            cout << "failed to open " << tempFile << '\n' << endl;
        } 
        else
        {
            bucketsPerGram = count[1]/(count[0]/1000);
            fileoutTemp << "\'" << endl;
            fileoutTemp << "\nTotal Gold: " << count[0]/1000 << "g" << "\tTotal buckets: " << count[1] << "\tBuckets for a gram: "<< bucketsPerGram << endl;
            fileoutTemp.close();
            
        }

        //removing the old file and renaming the new one, to make it look like it was just written to and not copied.
        remove(oldFile);
        int result = rename(newFile, oldFile);
        //displays statistics in the terminal.
        cout << "\nNew Gold added: " << weightOfGold << "mg" << endl;
        cout << "\nTotal Gold: " << count[0]/1000 << "g" << "\tTotal buckets: " << count[1] << "\tBuckets for a gram: "<< bucketsPerGram << endl;
        cout << "\nPress \"q\" to quit or \"c\" to continue" << endl;
        cin >> exitProgram;

    }
    return 0;
}    

//Makes a copy of current to temporary File, in order to get rid of the statisics at the bottom.
void copyFile(string fileNameLog, string tempFile, string fileContent){
    fstream fileoutLog;
    ofstream fileoutTemp;
    fileoutLog.open(fileNameLog);
    fileoutTemp.open(tempFile);
        while (fileContent != "\'"){
            getline(fileoutLog, fileContent);
            if (fileContent == "\'"){
                fileoutTemp.clear();
                fileoutTemp.close();
                cout << "[+]reached end of file" << endl;
            } else {
                fileoutTemp << fileContent << endl;
                cout << "[+]printing lines" << endl;
            }
        }
        fileoutLog.clear();
        fileoutLog.close();
        return;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName){


    // Return successful
    return 0;
}

//Adds the user entered data to the temporary file.
void addNewData(string tempFile, string fileNameDb, string fileContent, string dayOfDigging, double weightOfGold, int buckets, string comment){
    ofstream fileoutTemp;
    fstream fileoutDb;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char* errmsg;
    sqlite3* db;
    sqlite3_stmt* stat;
    sqlite3_open("GoldLogDb.db", &db);
    int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXIST GoldData(comment varchar(100),x1 INT, x2 INT, x3 INT, x4 INT);", callback, 0, &errmsg);
    if(rc != SQLITE_OK){
        cout << "error: " << errmsg;
    }
    else
    {
        string sql = "INSERT INTO GoldData(comment, x1) VALUES ('Hello',"+dayOfDigging+")";
        sqlite3_exec(db, sql.c_str(), callback, 0, &errmsg);
    }
    

    fileoutTemp.open(tempFile, std::ios_base::app);
        if (!fileoutTemp.is_open()) {
            cout << "failed to open " << tempFile << '\n' << endl;
        } 
        
        else {

            fileoutTemp << "Date: " << dayOfDigging << "\tGold: " << weightOfGold << "mg" << "\tBuckets: " << buckets << "\t#Comment: "<< comment << endl;
            cout << "[+]Done Writing!" << endl;

            fileoutDb.open(fileNameDb, std::ios_base::app);
            if (!fileoutDb.is_open()&&!fileoutTemp.is_open()) {
                cout << "failed to open " << fileNameDb << " or "<< tempFile << '\n' << endl;
            }
            else {
                fileoutDb << dayOfDigging << " " << 1 + ltm->tm_mon << " " << 1900 + ltm->tm_year << " " << weightOfGold << " " << buckets << endl;
                cout << "[+]Done Writing!" << endl;
                fileoutDb.close();
            }
        }
}   

//Keeps track of all the counting and adds that to an array which the values are taken out of in the main function.
int* counters(string fileNameDb){
    static int a[4];
    fstream fileoutDb;
    string fileContent;
    int wordCounter = 0;
    double totalWeightOfGold = 0;
    int totalBuckets = 0;
    int timesWentThere = 0;

    fileoutDb.open(fileNameDb);
        while (fileoutDb >> fileContent){
            int fileContentNum = stoi(fileContent);
                if (wordCounter==3){
                    totalWeightOfGold +=fileContentNum;
                    wordCounter++;
                }

                else if (wordCounter==4){
                    totalBuckets +=fileContentNum;
                    wordCounter = 0;
                    timesWentThere++;
                }
                        
                else{
                    wordCounter++;
                }                    
        }
    a[0] = totalWeightOfGold;
    a[1] = totalBuckets;
    a[2] = timesWentThere;
    fileoutDb.close();
    return a;
}
