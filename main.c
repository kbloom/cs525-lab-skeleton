#include <readline/readline.h>
#include <readline/history.h>
#include "ast.h"
#include "print.h"
#include <stdio.h>


int main(int argc, char** argv){
   char* input;
   statement_t* parsed=NULL;
   while ( (input = readline(">> ")) != 0 ){
      parsed=parseStatement(input);
      if (parsed){
	 /* parse succeded. determine which command was run */
	 if(parsed->select){
	    printSelectStatement(parsed->select);
	 }
	 if(parsed->insert){
	    printInsertStatement(parsed->insert);
	 }
	 if(parsed->createTable){
	    printCreateStatement(parsed->createTable);
	 }
	 if(parsed->dropTable){
	    printf("drop table %s;\n",parsed->dropTable);
	 }
	 if(parsed->printTable){
	    printf("print table %s;\n",parsed->printTable);
	 }
	 if(parsed->set){
	    printSetStatement(parsed->set);
	 }
	 if(parsed->parameterless == CMD_PRINT_CATALOG)
	    printf("print catalog;\n");
	 if(parsed->parameterless == CMD_PRINT_BUFFER)
	    printf("print buffer;\n");
	 if(parsed->parameterless == CMD_PRINT_HIT_RATE)
	    printf("print hit rate;\n");
	 if(parsed->parameterless == CMD_COMMIT)
	    printf("commit;\n");
	 if(parsed->parameterless == CMD_EXIT){
	    printf("exit;\n");
	    break;
	 }
      }else{
	 /* There was a syntax error, and the parser has already 
	  * printed an error message, so nothing to do here.*/
      }
      freeStatement(parsed);
      parsed=NULL;
   }
   freeStatement(parsed);
}
