#include <readline/readline.h>
#include <readline/history.h>
#include "ast.h"
#include "print.h"
#include <stdio.h>

int main(int argc, char** argv){
   char* input;
   statement_t* parsed=NULL;
   while ( (input = readline(">> ")) != 0 ){
      parsed=parse_statement(input);
      if (parsed){
	 /* parse succeded. determine which command was run */
	 if(parsed->select){
	    printSelectStatement(parsed->select);
	 }
	 if(parsed->insert){
	    printInsertStatement(parsed->insert);
	 }
	 if(parsed->create_table){
	    printCreateStatement(parsed->create_table);
	 }
	 if(parsed->drop_table){
	    printf("drop table %s;\n",parsed->drop_table);
	 }
	 if(parsed->print_table){
	    printf("print table %s;\n",parsed->print_table);
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
      free_statement(parsed);
      parsed=NULL;
   }
   free_statement(parsed);
}
