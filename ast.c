#include "ast.h"
#include <stdlib.h>

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
}
statement_t * parseStatement(char * stmt){
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
condition_t* newCondition(char* left_col, char* op, char* right_col, int num){
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

void freeIdList(id_list_t *);
void freeNumList(num_list_t*);
void freeCondition(condition_t *);
void freeSelectStatement(select_statement_t*);
void freeInsertStatement(insert_statement_t*);
void freeCreateStatement(create_statement_t*);
void freeSetStatement(set_statement_t*);

