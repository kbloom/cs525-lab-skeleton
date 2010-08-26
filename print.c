#include "print.h"
#include "stdio.h"

void print_id_list(id_list_t* i){
   while(i){
      printf("%s",i->id);
      if (i->next) printf(", ");
      i=i->next;
   }
}
void print_num_list(num_list_t* i){
   while(i){
      printf("%d",i->num);
      if (i->next) printf(", ");
      i=i->next;
   }
}
void print_condition(condition_t* i){
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
void print_select_statement(select_statement_t* i){
   printf("select ");
   if(i->fields)
      print_id_list(i->fields);
   else
      printf("*");
   printf(" from %s",i->table);
   if (i->conditions){
      printf(" where ");
      print_condition(i->conditions);
   }
   printf(";\n");
}
void print_insert_statement(insert_statement_t* i){
   printf("insert into %s values (", i->table);
   print_num_list(i->values);
   printf(");\n");
   
}
void print_create_table_statement(create_table_statement_t* i){
   printf("create table %s (", i->table);
   print_id_list(i->columns);
   printf(");\n");
}
void print_set_statement(set_statement_t* i){
   printf("set ");
   switch (i->variable){
      case CONFIG_TIMER: printf("timer "); break;
   }
   printf("%s;\n", i->value ? "on" : "off" );
}
