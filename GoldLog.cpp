
#include <iostream>
#include <string>
#include "sqlite3.h"
#include "myfunctions.hpp"

using namespace std;

int main() {
    char userInput;
    
    cout <<"      _____           _       _ "<< endl;
    cout <<"     / ____|         | |     | | "<< endl;
    cout <<"    | |  __    ___   | |    _| | "<< endl;
    cout <<"    | | |_ |  / _ \\  | |  / _` | "<< endl;
    cout <<"    | |__| | | (_) | | | | (_| | "<< endl;
    cout <<"     \\_____|  \\___/  |_|  \\__,_| "<< endl;

    while (userInput != 'q') {

        cout << "\nWould you like to add an entry(a) or print out the current statistics(s)? " << endl;
        cin >> userInput;

        if(userInput == 'a'){

            while (userInput != 'q' && userInput != 'e') {
                double totalWeight;
                string fileNameLog("GoldLog.txt");
                int buckets;
                string dateOfDigging;
                int sizeOfFile;
                int wordCounter = 0;
                double totalWeightOfGold = 0;
                int totalBuckets = 0;
                int timesWentThere = 0;
                string comment = "No comment.";
                double bucketsPerGram = 0;
                string nothing;

                //promting user for data
                cout << "\nEnter gold finding Date(DD.MM.YYYY): ";
                cin >> dateOfDigging;

                cout << "\nEnter weight of Flasque: ";
                cin >> totalWeight;
                cout << "\n";
                cout << "\nEnter bucket count: ";
                cin >> buckets;
                cout << "\nAdd a comment: ";
                getline(cin, nothing);
                getline(cin, comment);
                int weightOfGold = (totalWeight - 10.14)*1000;

                WriteToDataBase(dateOfDigging, to_string(weightOfGold), to_string(buckets), comment);

                cout << "\nWould you like to exit this function(e), quit the program(q) or continue(c)? ";
                cin >> userInput;
                cout << userInput << endl;

            }
    
        }
        else if(userInput == 's'){
            getDataFromDB();
            cout << "\nWould you like to quit the program(q) or continue(c)?";
            cin >> userInput;
        }
        else{
            cout << "\nNot a valid input" << endl;
        }
    }
return 0;   
}    

int callback(void *NotUsed, int argc, char **argv, char **azColName){  
    
    cout << "Total Gold: " << stod(argv[1])/1000 << "g" << "\tTotal Buckets: " << argv[2] << "\tBuckets per Gram: " << stod(argv[2])/(stod(argv[1])/1000) << endl;
    // Return successful
    return 0;
}

int WriteToDataBase(string dateOfDigging, string weightOfGold, string buckets, string comment){
    char* errmsg;
    sqlite3* db;
    sqlite3_stmt* stat;
    sqlite3_open("GoldLog.db", &db);
    string query = "CREATE TABLE IF NOT EXISTS GoldData(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, Date varchar(11), Gold INT, Buckets INT, Comment varchar(100));";
    int rc = sqlite3_exec(db, query.c_str() , callback, 0, &errmsg);
    if (rc != SQLITE_OK)
    {
        cout << errmsg << endl;
    }
    else {
    query = "INSERT INTO GoldData(Date, Gold, Buckets, Comment) VALUES (\""+dateOfDigging+"\", "+weightOfGold+", "+buckets+", \""+comment+"\")";
    rc = sqlite3_exec(db, query.c_str(), callback, 0, &errmsg);
        if (rc != SQLITE_OK)
        {
            cout << errmsg << endl;
        }
    }
    sqlite3_close(db);   
return 0;
}

int getDataFromDB(){
    char* errmsg;
    sqlite3* db;
    sqlite3_stmt* stat;
    sqlite3_open("GoldLog.db", &db);
    string query = "SELECT MAX(id), SUM(Gold), SUM(Buckets) FROM GoldData";
    int rc = sqlite3_exec(db, query.c_str() , callback, 0, &errmsg);
    return 0;
}
