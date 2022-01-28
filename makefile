all:
	lex proiect.l
	yacc -d proiect.y
	gcc -g y.tab.c lex.yy.c -o proiect
clean:
	rm -f *~proiect y.tab.c y.tab.h lex.yy.c
