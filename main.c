#include <readline/readline.h>
#include <readline/history.h>
#include "ast.h"
#include "sql.tab.h"
#include "sql.lex.h"
extern int yydebug;

int yyparse (void);

int main(int argc, char** argv){
   char* input;
   yydebug=1;
   while ( (input = readline(">> ")) != 0 ){
      char* t;
      for (t=input;*t;++t) *t=tolower(*t);
      yy_scan_string(input);
      yyparse();
   }
}
