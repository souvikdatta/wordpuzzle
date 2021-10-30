#ifndef __CMENU_HPP__
#define __CMENU_HPP__
#include "Common.hpp"
using namespace std;

class CMenu
{
public:
    void showMainMenu(difficultyLevels_e currDiffLevel=EASY);
    void showDifficultyLevelMenu();
    int getChoice(); 
    virtual ~CMenu()
    {
    }
};

void CMenu::showDifficultyLevelMenu()
{
    cout << "Difficulty Levels:-" << "\n";
    cout << "-------------------" << "\n";
    cout << "1. EASY" << "\n";
    cout << "2. MEDIUM" << "\n";
    cout << "3. HARD"<< "\n";
    cout << "4. Go back to Main Menu" << "\n"; 
}

void CMenu::showMainMenu(difficultyLevels_e currDiffLevel)
{
    string str;
    if(EASY == currDiffLevel)
        str = "EASY";
    else if(MEDIUM == currDiffLevel)
        str = "MEDIUM";
    else
        str = "HARD";

    system("clear");
    cout << "=======================" << endl;
    cout << "Welcome to Word Puzzle." << endl;
    cout << "=======================" << endl;
    cout << "1. Select Difficulty Level (Current Level is:" << str <<")" << endl;
    cout << "2. Show a WORD" << endl;
    cout << "3. About Author" << endl;
    cout << "4. Exit" << endl;
}

int CMenu::getChoice() 
{   
    string choice;
    while(choice.length() != 1)
    {
        cout << "Enter choice:"; 
        cin >> choice;
    }
    return stoi(choice);
}

#endif