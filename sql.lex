%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sql.tab.h"
void yyerror(const char *);
char *strdup(const char *s);
%}

%option ansi-prototypes noyywrap yy_scan_string

%%

select               return SELECT;
from	             return FROM;
where                return WHERE;
and                  return AND;
insert	             return INSERT;
into                 return INTO;
values               return VALUES;
create               return CREATE;
table                return TABLE;
print                return PRINT;
catalog              return CATALOG;
buffer               return BUFFER;
hit                  return HIT;
rate                 return RATE;
drop		     return DROP;
set                  return SET;
timer                return TIMER;
on                   {yylval.intVal = 1;  return BOOLEAN;}
off                  {yylval.intVal = 0;  return BOOLEAN;}
commit               return COMMIT;
exit                 return EXIT;
quit                 return EXIT;
"<"                  |
"="                  |
">"                  |
"<="                 |
">="                 |
"!="                 {yylval.stringVal = strdup(yytext); return OPERATOR;}
"("                  return *yytext;
")"                  return *yytext;
";"                  return *yytext;
","                  return *yytext;
"*"		     return *yytext;
[a-z][a-z0-9]*	     {yylval.stringVal = strdup(yytext); return IDENTIFIER;}
[0-9]+               {yylval.intVal = atoi(yytext); return NUMBER;}
[ \t]                {}
.                    {yyerror("Unknown Character");}

%%
