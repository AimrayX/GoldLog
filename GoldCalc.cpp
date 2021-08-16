
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

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

        time_t now = time(0);
        tm *ltm = localtime(&now);
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
        

        fileoutLog.open(fileNameLog);
        fileoutTemp.open(tempFile);
        while (fileContent != "\'"){
                    getline(fileoutLog, fileContent);
                    if (fileContent == "\'")
                    {
                        fileoutTemp.clear();
                        fileoutTemp.close();
                        cout << "[+]reached end of file" << endl;
                    }
                    else
                    {
                        fileoutTemp << fileContent << endl;
                        cout << "[+]printing lines" << endl;
                    }
        }
        fileoutLog.clear();
        fileoutLog.close();

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
                fileoutDb.open(fileNameDb);
                while (fileoutDb >> fileContent)
                {
                    int fileContentNum = stoi(fileContent);
                    if (wordCounter <= 4)
                    {
                        if (wordCounter==3)
                        {
                            totalWeightOfGold +=fileContentNum;
                            wordCounter++;
                        }

                        else if (wordCounter==4)
                        {
                            totalBuckets +=fileContentNum;
                            wordCounter = 0;
                            timesWentThere++;
                        }
                        
                        else
                        {
                            wordCounter++;
                        }
                          
                    }
                    
                }
                
            }
            fileoutDb.close();
            fileoutLog.close();
            fileoutTemp.close();
        }
        fileoutTemp.open(tempFile, std::ios_base::app);
        if (!fileoutTemp.is_open()) {
            cout << "failed to open " << tempFile << '\n' << endl;
        } 
        else
        {
            bucketsPerGram = totalBuckets/(totalWeightOfGold/1000);
            fileoutTemp << "\'" << endl;
            fileoutTemp << "\nTotal Gold: " << totalWeightOfGold/1000 << "g" << "\tTotal buckets: " << totalBuckets << "\tBuckets for a gram: "<< bucketsPerGram << endl;
            fileoutTemp.close();
            
        }
        remove(oldFile);
        int result = rename(newFile, oldFile);
        cout << "\nNew Gold added: " << weightOfGold << "mg" << endl;
        cout << "\nTotal Gold: " << totalWeightOfGold/1000 << "g" << "\tTotal buckets: " << totalBuckets << "\tBuckets for a gram: "<< bucketsPerGram << endl;
        cout << "\nPress \"q\" to quit or \"c\" to continue" << endl;
        cin >> exitProgram;
    }
    return 0;
}    
    

