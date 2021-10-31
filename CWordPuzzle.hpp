#include "CMenu.hpp"
#include "CGameEngine.hpp"
#include "CDatabase.hpp"

//Required for using shared_ptr
#include <memory>
#include "Common.hpp"

using namespace std;

class CWordPuzzle
{
private:
    //Think about replacing these with smart pointers
    std::shared_ptr<CDatabase> m_DB;
    std::shared_ptr<CMenu> m_Menu;
    std::shared_ptr<CGameEngine> m_GameEngine;

    int m_Score;
    int m_DifficultyLevel;

    CWordPuzzle();

public:

    //Singleton object
    static CWordPuzzle& getInstance()
    {
        static CWordPuzzle obj;
        return obj;
    }

    int getScore() const
    {
        return m_Score;
    }

    void setScore(const int score)
    {
        m_Score = score;
    }

    void startGame();

    
    virtual ~CWordPuzzle();
};

CWordPuzzle::CWordPuzzle():m_Score{0},m_DifficultyLevel{EASY}
{
    m_DB.reset(new CDatabase());
    m_Menu.reset(new CMenu());
    m_GameEngine.reset(new CGameEngine());
    // cout << "Construcor called" << "\n";
}

CWordPuzzle::~CWordPuzzle()
{
    // cout << "Destructor called" << "\n";
}

void CWordPuzzle::startGame()
{
    //Prepare DB
    m_DB->prepareDb("easy.txt", EASY);
    m_DB->prepareDb("medium.txt", MEDIUM);
    m_DB->prepareDb("hard.txt", HARD);
    
    // m_DB->printDB();

    //getchar();
    m_GameEngine->startGameEngine(m_Menu, m_DB);   

}


