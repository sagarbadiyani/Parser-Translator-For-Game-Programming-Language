test: parser.tab.c lex.yy.c driver.o
	gcc -o test parser.tab.c lex.yy.c driver.o

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: scanner.l
	flex -l scanner.l 

driver.o: driver.c
	gcc -c driver.c

clean: 
	rm -rf lex.yy.c parser.tab.c driver.o parser.tab.h test bison.tab.c