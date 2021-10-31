#ifndef __CGAMEENGINE_HPP__
#define __CGAMEENGINE_HPP__
#include <memory>
#include <unordered_map>
#include<bits/stdc++.h>
#include "CDatabase.hpp"
#include <time.h>
#include <thread>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

using namespace std;
static volatile bool done = false;

constexpr int penaltyEasy = -5;
constexpr int penaltyMedium = -10;
constexpr int penaltyHard = -15;
constexpr int scoreEasy = 5;
constexpr int scoreMedium = 10;
constexpr int scoreHard = 15;

class CMenu;
class CDatabase;
class CGameEngine
{
private:
    int m_diffLevel{static_cast<int>(EASY)};
    int m_score{0};
    void startWordGame(std::shared_ptr<CMenu> menu, std::shared_ptr<CDatabase> db);
    void updateScore(bool success);

public:
    void startGameEngine(std::shared_ptr<CMenu> menu, std::shared_ptr<CDatabase> db);
    virtual ~CGameEngine(){}
};

void CGameEngine::updateScore(bool success)
{
    int i, j;
    switch(m_diffLevel)
    {
        case EASY:
                i = penaltyEasy;
                j = scoreEasy;
            break;
        case MEDIUM:
                i = penaltyMedium;
                j = scoreMedium;            
            break;
        case HARD:
                i = penaltyHard;
                j = scoreHard;        
            break;

    }
    if(true == success)
        m_score += j;
    else
        m_score += i ;
}

void CGameEngine::startWordGame(std::shared_ptr<CMenu> menu, std::shared_ptr<CDatabase> dbPtr)
{
    
    //cout << "Inside Start Word Game" << endl;
    //Pick a random string from the difficulty bucket
    //Initialize the random seed
    int sizeOftheBucket = dbPtr->db[m_diffLevel].size();
    //TODO - Increase the randomness 
    srand (time(NULL));
    int randSelectionIndex = rand() % sizeOftheBucket + 0;
    //cout << "Ramdom Index is:" << randSelectionIndex << endl;
    int count = 0;
    string key, value, response;

    for(auto &i : dbPtr->db[m_diffLevel])
    {
        if(randSelectionIndex == count++)
        {
            key = i.first;
            value = i.second;
            break;
        }
    }

    //cout << "Key is:" << key <<" value:" << value << endl; 
    transform(value.begin(), value.end(), value.begin(), ::toupper);
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    getchar(); 
    system("clear");
    menu->showScore(m_score);
    cout << "************************************************" << endl;
    cout << "Idenify this word (within 10 secs):" << value << endl;
    cout << "************************************************" << endl;
    cout << "Enter your guess:";
    fflush(stdout);

    struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };

    std::string line;
    int ret = 0;
    bool success = false;
    bool inputGiven = false;
    while(ret == 0)
    {
        ret = poll(&pfd, 1, 10000);  // timeout of 1000ms
        if(ret == 1) // there is something to read
        {
            inputGiven = true;
            std::getline(std::cin, response);
            transform(response.begin(), response.end(), response.begin(), ::toupper);
            if(!key.compare(response))
            {
                success = true;
                updateScore(success);
                menu->showScore(m_score);
                system("clear");
                cout << "\n";
                cout << "* * * * *  * *\n";
                cout << "WELL DONE !!\a\a" << endl;
                cout << "* * * * *  * *\n";
                cout << "\n";
            }
            else
            {
                //inputGiven = false;
                system("clear");
                updateScore(success);
                cout << "\n";    
                cout << "Sorry, Wrong guess :(" << endl;
                std::cout << "-------------------" << endl;
                std::cout << "Solution:" << key << endl;
                std::cout << "-------------------" << endl;                    
                cout << "Better luck next time :)" << endl;
            }

            cout << "Hit any key to go to main menu ..." << endl;
            getchar();
        }
        break;
    }    

    

    if(inputGiven == false)
    {
        //success = false;
        system("clear");
        menu->showScore(m_score);
        cout << "\n";
        std::cout << " ** SORRY TIME OUT !!\a **" << endl;
        cout << "\n";
        std::cout << "-------------------" << endl;
        std::cout << " Solution : " << key << endl;
        std::cout << "-------------------" << endl;
        cout << "\n";
        cout << "Hit any key to go to main menu ..." << endl;
        fflush(stdout);
        getchar();
    }
}

void CGameEngine::startGameEngine(std::shared_ptr<CMenu> menu, std::shared_ptr<CDatabase> db)
{
    int choice = 0;
    // int temp;
    bool loop = 1;
    
    while(loop)
    {
        switch(choice)
        {
            case 1:
                system("clear");
                menu->showDifficultyLevelMenu();
                while(1)
                {
                    choice = menu->getChoice();
                    if(choice >=1 && choice <=3)
                    {
                        m_diffLevel = choice - 1 ; //To adjust with enum - difficultyLevels_e
                        choice = -1;    
                        break;
                    }
                    else if (4 == choice)
                    {
                        choice = -1; //Default case
                        break;    
                    }
                    else
                    {
                        cout << "Wrong choice. Please enter a valid choice" << endl;
                        cin.clear();
                        fflush(stdin);                        
                    }
                }
                break;
            case 2:
                    // cout << "About to call startWordGame()" << endl;
                    // getchar();
                    startWordGame(menu, db);
                    choice = -1;
                    break;
                break;
            case 3:
                    system("clear");
                    cout << "\n";
                    cout << "****************************" << "\n";
                    cout << "*                          *" << "\n";
                    cout << "*  Thank you and Good Bye  *" << "\n";
                    cout << "*                          *" << "\n";
                    cout << "*  - Souvik                *" << "\n";
                    cout << "*                          *" << "\n";
                    cout << "****************************" << "\n";
                    cout << "\n";
                    loop = 0;
                    break;  
            default:
                system("clear");
                if(0 == choice)
                    menu->showWelcomeBanner();
                else
                    menu->showScore(m_score);
                menu->showMainMenu(static_cast<difficultyLevels_e>(m_diffLevel));
                while(1)
                {
                    choice = menu->getChoice();
                    if(choice >=1 && choice <=4)
                        break;
                    else
                    {
                        cout << "Wrong choice entered. Please enter a valid choice" << endl;
                        cin.clear();
                        fflush(stdin);                          
                    }
                }
        }   
    }
}


#endif