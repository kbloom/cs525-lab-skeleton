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
	 /*
	  * dispatch_print is an example of how to work with the AST to detect
	  * and run the various commands, as well as how to get at all of the
	  * information in the AST. Remove this call when you implement the
	  * logic to actually run the commands in the DBMS.
	  * (You can use the functions in print.c for debugging purposes)
	  */
	 dispatch_print(parsed);
	 if(parsed->parameterless == CMD_EXIT){
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

