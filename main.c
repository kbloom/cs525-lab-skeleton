#include "parser.h"
#include "print.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

//consider using the GNU Readline library instead of myreadline()
//it has a similar interface, and you'll get nice features like working
//cursor keys and (if initialized properly) history.
//run "man 3 readline" for more information
char* myreadline(char* prompt);

int main(int argc, char** argv){
   char* input=NULL;
   statement_t* parsed=NULL;
   int stillrunning=1;
   while (stillrunning &&  (input=myreadline(">> ")) != 0){
      parsed=parse_statement(input);
      if (parsed){
	 /* parse succeded. determine which command was run */
	 if(parsed->select){
	    print_select_statement(parsed->select);
	 }
	 if(parsed->insert){
	    print_insert_statement(parsed->insert);
	 }
	 if(parsed->create_table){
	    print_create_table_statement(parsed->create_table);
	 }
	 if(parsed->drop_table){
	    printf("drop table %s;\n",parsed->drop_table);
	 }
	 if(parsed->print_table){
	    printf("print table %s;\n",parsed->print_table);
	 }
	 if(parsed->set){
	    print_set_statement(parsed->set);
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
	    stillrunning=0;
	 }
      }else{
	 /* There was a syntax error, and the parser has already 
	  * printed an error message, so nothing to do here.*/
      }
      free(input);            input=NULL;
      free_statement(parsed); parsed=NULL;
   }
}

char* myreadline(char* prompt){
   char* input=NULL;
   size_t inputlength=0;
   printf("%s",prompt);
   if (getline(&input,&inputlength,stdin)!=-1)
      return input;
   else
      return input;
}

