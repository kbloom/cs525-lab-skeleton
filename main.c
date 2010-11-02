#include "parser.h"
#include "print.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

time_t now();

//consider using the GNU Readline library instead of myreadline()
//it has a similar interface, and you'll get nice features like working
//cursor keys and (if initialized properly) history.
//run "man 3 readline" for more information
char* myreadline(char* prompt);

int main(int argc, char** argv){
   char* input=NULL;
   statement_t* parsed=NULL;
   int stillrunning=1;
   int timing=0;
   while (stillrunning &&  (input=myreadline(">> ")) != 0){
      parsed=parse_statement(input);
      if (parsed){
	 time_t begintime=now();
	 /*
	  * dispatch_print is an example of how to work with the AST to detect
	  * and run the various commands, as well as how to get at all of the
	  * information in the AST. Remove this call when you implement the
	  * logic to actually run the commands in the DBMS.
	  * (You can use the functions in print.c for debugging purposes)
	  */
	 dispatch_print(parsed);
	 if(parsed->set && parsed->set->variable == CONFIG_TIMER)
	    timing = parsed->set->value;
	 if(parsed->parameterless == CMD_EXIT){
	    stillrunning=0;
	 }
	 time_t endtime=now();
	 if (timing)
	    printf("Elapsed time: %dus\n", endtime-begintime);
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

time_t now(){
   struct timeval t;
   gettimeofday(&t,0);
   return t.tv_sec*1000000+t.tv_usec;
}
