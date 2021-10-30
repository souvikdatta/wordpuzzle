#include <iostream>
#include "CWordPuzzle.hpp"

using namespace std;

int main(int argc, char **argv)
{
    CWordPuzzle o = CWordPuzzle::getInstance();
    o.startGame();

    return 0;
}