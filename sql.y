%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
void yyerror(const char *);
int yylex(void);
%}

%debug

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
%token <stringVal> OPERATOR
%token <stringVal> IDENTIFIER
%token <intVal> NUMBER

%union{
   char* stringVal;
   int intVal;
   struct id_t* idList;
   struct num_t* numList;
   struct condition_t* conditionList;
   struct select_statement_t* selectStatement;
   struct create_statement_t* createStatement;
   struct insert_statement_t* insertStatement;
}

%type <idList> ID_LIST
%type <numList> NUM_LIST
%type <conditionList> CONDITION
%type <conditionList> COND_LIST
%type <idList> S_FIELDS
%type <selectStatement> SELECT_S
%type <createStatement> CREATE_S
%type <insertStatement> INSERT_S


%start STATEMENT


%%

ID_LIST	    : IDENTIFIER				        { $$ = newId($1)}
            | IDENTIFIER ',' ID_LIST                            { $$ = newId($1); $$->next = $3}
            ;
NUM_LIST    : NUMBER					        { $$ = newNum($1)}
	    | NUMBER ',' NUM_LIST                               { $$ = newNum($1); $$->next = $3}
            ;
CONDITION   : IDENTIFIER OPERATOR IDENTIFIER              	{ $$ = newCondition($1,$2,$3,0) }	 
	    | IDENTIFIER OPERATOR NUMBER                        { $$ = newCondition($1,$2,NULL,$3) }
            ;
COND_LIST   : CONDITION                                         { $$ = $1 }
	    | CONDITION AND COND_LIST                           { $$ = $1; $$->next = $3; }
	    ;
S_FIELDS    : ID_LIST					        { $$ = $1 }
	    | '*'					        { $$ = NULL }
            ;
SELECT_S    : SELECT S_FIELDS FROM IDENTIFIER                   { $$ = newSelectStatement($2,$4,NULL) }
	    | SELECT S_FIELDS FROM IDENTIFIER WHERE COND_LIST   { $$ = newSelectStatement($2,$4,$6)   }
	    ;
INSERT_S    : INSERT INTO IDENTIFIER VALUES '(' NUM_LIST ')'    { $$ = newInsertStatement($3,$6) }
	    ;
CREATE_S    : CREATE TABLE IDENTIFIER '(' ID_LIST ')'           { $$ = newCreateStatement($3,$5) }
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
STATEMENT   : SELECT_S ';'
	    | INSERT_S ';'
	    | CREATE_S ';'
            | PRINT_S ';'
            | SET_S ';'
            | COMMIT ';'
            | EXIT ';'

%%

void yyerror (const char *s){
   fprintf(stderr, "%s\n", s);
}
