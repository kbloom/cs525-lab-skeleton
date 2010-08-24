#define SQL_PARSER_INTERNAL
#include "ast.h"
#include <stdlib.h>
#include <ctype.h>
#include "sql.tab.h"
#include "sql.lex.h"

int yyparse(void);

statement_t* returned_statement;

//user-visible functions
int lengthIdList(const id_list_t *it){
   int i=0;
   while(it){
      ++i;
      it=it->next;
   }
   return i;
}
int lengthNumList(const num_list_t *it){
   int i=0;
   while(it){
      ++i;
      it=it->next;
   }
   return i;
}
void freeStatement(statement_t* i){
   if(!i) return;
   freeSelectStatement(i->select);
   freeCreateStatement(i->createTable);
   freeInsertStatement(i->insert);
   free(i->dropTable);
   free(i->printTable);
   freeSetStatement(i->set);
   free(i);
}
statement_t * parseStatement(char * input){
   char* t;
   for (t=input;*t;++t) *t=tolower(*t);
   yy_scan_string(input);
   if (yyparse()==0)
      return returned_statement;
   else
      return NULL;
}


//internal parser functions
id_list_t* newIdList(char* id){
   id_list_t* i=malloc(sizeof(id_list_t));
   i->id=id;
   i->next=NULL;
   return i;
}
num_list_t* newNumList(int num){
   num_list_t* i=malloc(sizeof(num_list_t));
   i->num=num;
   i->next=NULL;
   return i;
}
condition_t* newCondition(char* left_col, char* op, char* right_col, int right_num){
   condition_t* i=malloc(sizeof(condition_t));
   i->left_col=left_col;
   i->op=op;
   i->right_col=right_col;
   i->right_num=right_num;
   i->next=NULL;
   return i;
}
select_statement_t* newSelectStatement(id_list_t* fields, char* table, condition_t* conds){
   select_statement_t* i=malloc(sizeof(select_statement_t));
   i->fields=fields;
   i->table=table;
   i->conditions=conds;
   return i;
}
insert_statement_t* newInsertStatement(char* table, num_list_t* values){
   insert_statement_t* i=malloc(sizeof(insert_statement_t));
   i->table=table;
   i->values=values;
   return i;
}
create_statement_t* newCreateStatement(char* table, id_list_t* columns){
   create_statement_t* i=malloc(sizeof(create_statement_t));
   i->table=table;
   i->columns=columns;
   return i;
}
set_statement_t* newSetStatement(variable_t variable, int value){
   set_statement_t* i=malloc(sizeof(set_statement_t));
   i->variable=variable;
   i->value=value;
   return i;
}
statement_t* newStatement(void){
   statement_t* i=malloc(sizeof(statement_t));
   i->select=NULL;
   i->createTable=NULL;
   i->insert=NULL;
   i->dropTable=NULL;   
   i->printTable=NULL;
   i->set=NULL;
   i->parameterless=CMD_NONE;
   return i;
}

void freeIdList(id_list_t *i){
   id_list_t* temp;
   while(i){
      temp=i->next;
      free(i->id);
      free(i);
      i=temp;
   }
}
void freeNumList(num_list_t* i){
   num_list_t* temp;
   while(i){
      temp=i->next;
      free(i);
      i=temp;
   }
}
void freeCondition(condition_t * i){
   condition_t* temp;
   while(i){
      temp=i->next;
      free(i->left_col);
      free(i->op);
      free(i->right_col);
      free(i);
      i=temp;
   }
}
void freeSelectStatement(select_statement_t* i){
   if(!i) return;
   freeIdList(i->fields);
   free(i->table);
   freeCondition(i->conditions);
   free(i);
}
void freeInsertStatement(insert_statement_t* i){
   if(!i) return;
   free(i->table);
   freeNumList(i->values);
   free(i);
}
void freeCreateStatement(create_statement_t* i){
   if(!i) return;
   free(i->table);
   freeIdList(i->columns);
   free(i);
}
void freeSetStatement(set_statement_t* i){
   if(!i) return;
   free(i);
}

