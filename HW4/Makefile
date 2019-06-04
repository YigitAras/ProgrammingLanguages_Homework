all:
	bison -d 17519-hw4.y
	flex 17519-hw4.flx
	gcc -o 17519-hw4 17519-hw4.tab.c lex.yy.c  17519-hw4.c -lfl
rm:
	rm lex.yy.c
	rm 17519-hw4.tab.h
	rm 17519-hw4.tab.c
