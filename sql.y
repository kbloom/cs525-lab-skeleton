%{
#include <stdio.h>
void yyerror(const char *);
%}
%token SELECT
%token FROM
%token WHERE
%token AND
%token INSERT
%token INTO
%token VALUES
%token CREATE
%token TABLE
%token PRINT
%token CATALOG
%token BUFFER
%token HIT
%token RATE
%token SET
%token TIMER
%token BOOLEAN
%token COMMIT
%token EXIT
%token EXIT
%token <stringVal> OPERATOR
%token <stringVal> IDENTIFIER
%token <intVal> NUMBER

%union{
   char* stringVal;
   int intVal;
}

%%

ID_LIST	    : IDENTIFIER
	    | IDENTIFIER ',' ID_LIST
            ;
NUM_LIST    : NUMBER
	    | NUMBER ',' NUM_LIST
            ;
CONDITION   : IDENTIFIER OPERATOR IDENTIFIER
	    | IDENTIFIER OPERATOR NUMBER
            ;
COND_LIST   : CONDITION
	    | CONDITION AND COND_LIST
	    ;
S_FIELDS    : ID_LIST
	    | '*'
            ;
SELECT_S    : SELECT S_FIELDS FROM IDENTIFIER
	    | SELECT S_FIELDS FROM IDENTIFIER WHERE COND_LIST
	    ;
INSERT_S    : INSERT INTO IDENTIFIER VALUES '(' NUM_LIST ')'
	    ;
CREATE_S    : CREATE TABLE IDENTIFIER '(' ID_LIST ')'
	    ;
PRINT_S     : PRINT CATALOG
	    | PRINT BUFFER
            | PRINT HIT RATE
            | PRINT TABLE IDENTIFIER
            ;
VARIABLE    : TIMER
	    ;
SET_S       : SET VARIABLE BOOLEAN
	    ;
STATEMENT   : SELECT_S
	    | INSERT_S
	    | CREATE_S
            | PRINT_S
            | SET_S
            | COMMIT
            | EXIT

%%

void yyerror (const char *s){
   fprintf(stderr, "%s\n", s);
}
