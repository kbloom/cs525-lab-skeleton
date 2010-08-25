#include "print.h"
#include "stdio.h"

void printIdList(id_list_t* i){
   while(i){
      printf("%s",i->id);
      if (i->next) printf(", ");
      i=i->next;
   }
}
void printNumList(num_list_t* i){
   while(i){
      printf("%d",i->num);
      if (i->next) printf(", ");
      i=i->next;
   }
}
void printCondition(condition_t* i){
   while(i){
      printf("%s ", i->left_col);
      switch(i->op){
	 case OP_EQUAL: printf("="); break;
      }
      if (i->right_col)
	 printf (" %s", i->right_col);
      else
	 printf (" %d", i->right_num);
      if (i->next) printf(" and ");
      i=i->next;
   }
}
void printSelectStatement(select_statement_t* i){
   printf("select ");
   if(i->fields)
      printIdList(i->fields);
   else
      printf("*");
   printf(" from %s",i->table);
   if (i->conditions){
      printf(" where ");
      printCondition(i->conditions);
   }
   printf(";\n");
}
void printInsertStatement(insert_statement_t* i){
   printf("insert into %s values (", i->table);
   printNumList(i->values);
   printf(");\n");
   
}
void printCreateTableStatement(create_table_statement_t* i){
   printf("create table %s (", i->table);
   printIdList(i->columns);
   printf(");\n");
}
void printSetStatement(set_statement_t* i){
   printf("set ");
   switch (i->variable){
      case CONFIG_TIMER: printf("timer "); break;
      case CONFIG_INDEX_DEBUG: printf("index debug "); break;
   }
   printf("%s;\n", i->value ? "on" : "off" );
}
