#ifndef __CMENU_HPP__
#define __CMENU_HPP__
#include "Common.hpp"
using namespace std;

class CMenu
{
public:
    void showMainMenu(difficultyLevels_e currDiffLevel=EASY);
    void showDifficultyLevelMenu();
    void showWelcomeBanner();
    void showScore(const int score);
    int getChoice(); 
    virtual ~CMenu()
    {
    }
};

void CMenu::showWelcomeBanner()
{
    system("clear");
    cout << "=======================" << endl;
    cout << "Welcome to Word Puzzle" << endl;
    cout << "=======================" << endl;
}

void CMenu::showScore(const int score)
{
    cout << "\n";
    cout << "= = = = = = = = = = = = = =" << endl;
    cout << "  Your Score : " << score << "\n";   
    cout << "= = = = = = = = = = = = = =" << endl;    
    cout << "\n";
}

void CMenu::showDifficultyLevelMenu()
{
    cout << "=================" << "\n";
    cout << "Difficulty Levels" << "\n";
    cout << "=================" << "\n";
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

    cout << "1. Select Difficulty Level (Current Level is:" << str <<")" << endl;
    cout << "2. Show a WORD" << endl;
    cout << "3. Exit" << endl;
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