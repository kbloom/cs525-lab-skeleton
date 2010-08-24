#include <readline/readline.h>
#include <readline/history.h>
#include "ast.h"

int main(int argc, char** argv){
   char* input;
   while ( (input = readline(">> ")) != 0 ){
      statement_t* parsed=parseStatement(input);
      if (parsed){
	 //TODO: put your dispach logic in here
	 printf("Foo\n");
      }
      freeStatement(parsed);
   }
}
