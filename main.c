#include <readline/readline.h>
#include <readline/history.h>
#include "sql.tab.h"
#include "sql.lex.h"

int yyparse (void);

int main(int argc, char** argv){
   char* input;
   while ( (input = readline(">> ")) != 0 ){
      char* t;
      for (t=input;*t;++t) *t=tolower(*t);
      yy_scan_string(input);
      yyparse();
   }
}
