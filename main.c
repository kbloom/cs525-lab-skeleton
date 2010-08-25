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
	    printSelectStatement(parsed->select);
	 }
	 if(parsed->insert){
	    printInsertStatement(parsed->insert);
	 }
	 if(parsed->create_table){
	    printCreateTableStatement(parsed->create_table);
	 }
	 if(parsed->create_index){
	    printf("create index %s on %s (%s);\n",
		  parsed->create_index->index,
		  parsed->create_index->table,
		  parsed->create_index->column);
	 }
	 if(parsed->drop_table){
	    printf("drop table %s;\n",parsed->drop_table);
	 }
	 if(parsed->drop_index){
	    printf("drop index %s of table %s;\n",
		  parsed->drop_index->index,
		  parsed->drop_index->table);
	 }
	 if(parsed->print_table){
	    printf("print table %s;\n",parsed->print_table);
	 }
	 if(parsed->print_index){
	    printf("print index %s of table %s;\n",
		  parsed->print_index->index,
		  parsed->print_index->table);
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

