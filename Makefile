CC=g++
CFLAGS=-I.
DEPS=CDatabase.hpp CGameEngine.hpp CMenu.hpp Common.hpp CWordPuzzle.hpp

wordpuzzle:wordpuzzle.o
	${CC} wordpuzzle.o -o wordpuzzle

wordpuzzle.o:wordpuzzle.cpp ${DEPS}
	${CC} -g wordpuzzle.cpp -c

clean:
	rm *.o wordpuzzle