#ifndef PRINT_H
#define PRINT_H
#include "parser.h"

#ifdef __cplusplus
extern "C"{
#endif


void printIdList(id_list_t* i);
void printNumList(num_list_t* i);
void printCondition(condition_t* i);
void printSelectStatement(select_statement_t* i);
void printInsertStatement(insert_statement_t* i);
void printCreateStatement(create_table_statement_t* i);
void printSetStatement(set_statement_t* i);

#ifdef __cplusplus
}
#endif
#endif
