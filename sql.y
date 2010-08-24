%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SQL_PARSER_INTERNAL
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
%token DROP
%token TIMER
%token <intVal> BOOLEAN
%token COMMIT
%token EXIT
%token <stringVal> OPERATOR
%token <stringVal> IDENTIFIER
%token <intVal> NUMBER

%union{
   char* stringVal;
   int intVal;
   struct id_list_t* idList;
   struct num_list_t* numList;
   struct condition_t* conditionList;
   struct select_statement_t* selectStatement;
   struct create_statement_t* createStatement;
   struct insert_statement_t* insertStatement;
   enum variable_t variable;
   struct set_statement_t* setStatement;
   enum parameterless_statement_t parameterlessStatement;
   struct statement_t* statement;
}

%type <idList> ID_LIST
%type <numList> NUM_LIST
%type <conditionList> CONDITION
%type <conditionList> COND_LIST
%type <idList> S_FIELDS
%type <selectStatement> SELECT_S
%type <createStatement> CREATE_T_S
%type <insertStatement> INSERT_S
%type <variable> VARIABLE
%type <setStatement> SET_S
%type <stringVal> DROP_T_S
%type <stringVal> PRINT_T_S
%type <parameterlessStatement> NOPARAM_S
%type <statement> STATEMENT

%start STATEMENT


%%

ID_LIST	    : IDENTIFIER				        { $$ = newIdList($1)}
            | IDENTIFIER ',' ID_LIST                            { $$ = newIdList($1); $$->next = $3}
            ;
NUM_LIST    : NUMBER					        { $$ = newNumList($1)}
	    | NUMBER ',' NUM_LIST                               { $$ = newNumList($1); $$->next = $3}
            ;
CONDITION   : IDENTIFIER OPERATOR IDENTIFIER              	{ $$ = newCondition($1,$2,$3,0xDEADBEEF) }
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
CREATE_T_S  : CREATE TABLE IDENTIFIER '(' ID_LIST ')'           { $$ = newCreateStatement($3,$5) }
	    ;
DROP_T_S    : DROP TABLE IDENTIFIER                             { $$ = $3 }
	    ;
PRINT_T_S   : PRINT TABLE IDENTIFIER			        { $$ = $3 }
	    ;
VARIABLE    : TIMER					        { $$ = CONFIG_TIMER }
	    ;
SET_S       : SET VARIABLE BOOLEAN			        { $$ = newSetStatement($2,$3) }
	    ;
NOPARAM_S   : PRINT CATALOG				        { $$ = CMD_PRINT_CATALOG }
	    | PRINT BUFFER				        { $$ = CMD_PRINT_BUFFER }
            | PRINT HIT RATE                                    { $$ = CMD_PRINT_HIT_RATE }
	    | COMMIT					        { $$ = CMD_COMMIT }
	    | EXIT                                              { $$ = CMD_EXIT }
            ;
STATEMENT   : SELECT_S ';'				        { returned_statement = newStatement(); returned_statement->select=$1;}
	    | INSERT_S ';'                                      { returned_statement = newStatement(); returned_statement->insert=$1;}
	    | CREATE_T_S ';'                                    { returned_statement = newStatement(); returned_statement->createTable=$1;}
	    | DROP_T_S ';'                                      { returned_statement = newStatement(); returned_statement->dropTable=$1;}
	    | PRINT_T_S ';'				        { returned_statement = newStatement(); returned_statement->printTable=$1;}
            | SET_S ';'                                         { returned_statement = newStatement(); returned_statement->set=$1;}
            | NOPARAM_S ';'                                     { returned_statement = newStatement(); returned_statement->parameterless=$1;}
	    ;
%%

void yyerror (const char *s){
   fprintf(stderr, "%s\n", s);
}
