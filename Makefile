CC=g++
wordpuzzle.o:CDatabase.hpp CGameEngine.hpp CMenu.hpp Common.hpp CWordPuzzle.hpp
	${CC} -g wordpuzzle.cpp -I. -c

all:wordpuzzle.o
	${CC} wordpuzzle.o -o wordpuzzle

clean:
	rm *.o wordpuzzle