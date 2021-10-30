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

class CMenu;
class CDatabase;
class CGameEngine
{
private:
    int m_diffLevel{static_cast<int>(EASY)};
    void startWordGame(std::shared_ptr<CDatabase> db);
public:
    void startGameEngine(std::shared_ptr<CMenu> menu, std::shared_ptr<CDatabase> db);
    void delay(int delayInMS);
    virtual ~CGameEngine(){}
};
#if 0
std::string readStdIn()
{
    struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };

    std::string line;
    int ret = 0;
    while(ret == 0)
    {
        ret = poll(&pfd, 1, 1000);  // timeout of 1000ms
        if(ret == 1) // there is something to read
        {
            std::getline(std::cin, line);
            transform(response.begin(), response.end(), response.begin(), ::toupper);
            if(!key.compare(response))
                cout << " BINGO :) !! " << endl;
            else
                cout << "Sorry Wrong guess :( !!" << endl;
            
            cout << "Hit any key to go to main menu" << endl;
            done = true;
            getchar();
            getchar();
        }
        else if(ret == -1)
        {
            std::cout << "Sorry time out !!: " std::endl;
        }
    }
    return line;
}
#endif
#if 0
void getInput (string key)
{
    string response;
    cin >> response;
    //Update the volatile flag
    //Compare the answer
    transform(response.begin(), response.end(), response.begin(), ::toupper);
    if(!key.compare(response))
        cout << " BINGO :) !! " << endl;
    else
        cout << "Sorry Wrong guess :( !!" << endl;
    
    cout << "Hit any key to go to main menu" << endl;
    done = true;
    getchar();
    getchar();
}
#endif

void CGameEngine::startWordGame(std::shared_ptr<CDatabase> dbPtr)
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
    cout << "************************************************" << endl;
    cout << "Idenify this word (within 10 secs):" << value << endl;
    cout << "************************************************" << endl;
    cout << "Enter your guess:";
    fflush(stdout);

    struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };

    std::string line;
    int ret = 0;
    bool done = false;
    while(ret == 0)
    {
        ret = poll(&pfd, 1, 10000);  // timeout of 1000ms
        if(ret == 1) // there is something to read
        {
            done = true;
            std::getline(std::cin, response);
            transform(response.begin(), response.end(), response.begin(), ::toupper);
            if(!key.compare(response))
            {
                cout << "\n";
                cout << "* * * * *  * *\n";
                cout << "WELL DONE :) !!\a\a" << endl;
                cout << "* * * * *  * *\n";
                cout << "\n";
            }
            else
            {
                cout << "\n";    
                cout << "Sorry, Wrong guess :(!!" << endl;
                std::cout << "-------------------" << endl;
                std::cout << "Solution:" << key << endl;
                std::cout << "-------------------" << endl;                    
            }

            cout << "Hit any key to go to main menu ..." << endl;
            getchar();
        }
        break;
    }    

    if(done == false)
    {
        system("clear");
        std::cout << "Sorry timed out !!" << endl;
        cout << "\n";
        std::cout << "-------------------" << endl;
        std::cout << "Solution:" << key << endl;
        std::cout << "-------------------" << endl;
        cout << "\n";
        cout << "Hit any key to go to main menu" << endl;
        fflush(stdout);
        getchar();
    }

#if 0
    //Take this input in a separatet thread context and in paralle start a beep time
    std::thread getUserInputThread( getInput, key);
    //Start "Dong thread"
    for(int i=0; i<10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << "\a";
        fflush(stdout);
        if(done == true)
            break;
    }

    if(false == done)
    {
        cout << "Sorry Time out !!" << endl;
        //getchar();
    }
#endif


    // std::thread::native_handle_type th = getUserInputThread.native_handle();
    // getUserInputThread.detach();
    // //Native thread Cancel
    // pthread_cancel(th);
}

void CGameEngine::delay(int delayInMS)
{
    clock_t start = clock();

    while(clock() < delayInMS + start);

    return;
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
                    startWordGame(db);
                    choice = -1;
                    break;
                break;
            case 3:

            case 4:
                    cout << "Thank you and Good Bye !!" << "\n";
                    loop = 0;
                    break;  
            default:
                system("clear");
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