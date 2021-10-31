#ifndef __CDATABASE_HPP__
#define __CDATABASE_HPP__
#include <array>
#include <unordered_map>
#include "Common.hpp"
#include <fstream>

class CDatabase
{
private:
    
    friend class CGameEngine;

public:
    array<unordered_map<string, string>, 3> db;
    void printDB();
    virtual ~CDatabase(){}
    int prepareDb(string nameOfFileWithWordList, difficultyLevels_e diffLevel);
};

//Use try and catch
int CDatabase::prepareDb(string nameOfFileWithWordList, difficultyLevels_e diffLevel)
{
    int retStatus = 0;
    string str, obsStr;
    int i,j;
    char temp;
    ifstream ifs (nameOfFileWithWordList);
    
    if(ifs.is_open())
    {
        while(std::getline(ifs, str))
        {
            //Insert into map - string + obfuscated string both
            //cout<< str << endl;
            obsStr = str;
            //obscure the string and store it as a value
            srand(time(NULL));
            #if 0
            for(int k=0; k<50; k++)
            {
                i = rand() % (obsStr.size()-1);                   
                temp = obsStr[i];
                j = rand() % (obsStr.size()-1); 
                //Jut to make sure that I donot lose any cycle where i and j are same
                if(i == j)
                {
                    k--;
                    continue;
                }
                obsStr[i] = obsStr[j];
                obsStr[j] = temp;
                //std::swap(obsStr[i],obsStr[j]);
                //cout << obsStr << endl;
            }
            #endif
            std::random_shuffle (obsStr.begin(), obsStr.end());
            //Ignore that key
            if(str.compare(obsStr) != 0)
                db[diffLevel].insert(std::pair<string, string>(str,obsStr));
        }
        
        // cout << "Size of Easy Map is:" << db[diffLevel].size() << endl;

        ifs.close();
    }

    return retStatus;
}

void CDatabase::printDB()
{
    for(int i=0; i<db.size(); i++)
        for(auto j: db[i])
            cout << j.first << ":" << j.second << endl;
        // cout << "----" << "\n";
}

#endif