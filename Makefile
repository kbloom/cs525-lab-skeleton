CFLAGS=-g -std=c99
parser:	sql.tab.o lex.yy.o main.o parser.o print.o
	$(CC) $(CFLAGS) $^ -o parser -lreadline

sql.tab.c sql.tab.h: sql.y
	bison --defines sql.y
lex.yy.c: sql.lex
	flex --header-file=sql.lex.h sql.lex
lex.yy.o: lex.yy.c sql.tab.h
	$(CC) $(CFLAGS) -D_POSIX_SOURCE -c $<
sql.tab.o: sql.tab.c sql.tab.h
main.o: main.c sql.tab.h
parser.o: parser.c parser.h
