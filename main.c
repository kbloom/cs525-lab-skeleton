#include <readline/readline.h>
#include <readline/history.h>
#include "ast.h"

int main(int argc, char** argv){
   char* input;
   statement_t* parsed=NULL;
   while ( (input = readline(">> ")) != 0 ){
      parsed=parseStatement(input);
      if (parsed){
	 //TODO: put your dispach logic in here
	 printf("Foo\n");
	 if(parsed->parameterless == CMD_EXIT) break;
      }
      freeStatement(parsed);
      parsed=NULL;
   }
   freeStatement(parsed);
}
