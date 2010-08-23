#include <readline/readline.h>
#include <readline/history.h>
#include "sql.tab.h"

int main(int argc, char** argv){
   char* input;
   while ( (input = readline(">> ")) != 0 ){
      yy_scan_buffer(input);
      yyparse();
   }
}
