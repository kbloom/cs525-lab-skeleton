#ifndef AST_H
#define AST_H

/**
 * A singly linked-list of identifiers (either table names or column names)
 */
typedef struct id_t{
   char* id;
   struct id_t* next;
} id_t;

/**
 * A singly-linked list of numbers.
 */
typedef struct num_t{
   int id;
   struct num_t* next;
} num_t;


/**
 * This is a linked list of conditions in the WHERE clause
 * left_col is the column name that appeared on the left side of the operator
 * op is the operator (< = > != <= >=)
 * right_col is the column name that appeared on the right side of the operator
 * if right_col is null, then the parser found a comparison to a number (e.g. WHERE A=3)
 * next points to the next condition in the list
 */
typedef struct condition_t{
   char* left_col;
   char* op;
   char* right_col;
   int right_num;
   struct condition_t* next;
} condition_t;


/**
 * This holds all of the information that was in a SELECT statement.
 * When we introduce joins in assignment 3, I will introduce a new data
 * structure (join_statement_t) to hold the parse tree for those.
 */
typedef struct select_statement_t{
   /// a singly-linked list of the fields listed in the SELECT clause
   /// This will be NULL in SELECT * statements.
   id_t* fields;
   /// the name of the table in the FROM clause
   char* table;
   /// a singly-linked list of the consitions in the WHERE clause.
   /// This will be null if there was no WHERE clause.
   condition_t* conditions;
} select_statement_t;


/**
 * This holds all of the information that was in an INSERT statement.
 */
typedef struct insert_statement_t{
   /// the name of the table to insert into
   char* table;
   /// a singly-list of the numbers to insert
   num_t* values;
} insert_statement_t;


/**
 * This holds all of the information that was in a CREATE TABLE statement.
 */
typedef struct create_statement_t{
   /// the name of the table to create
   char* table;
   /// a singly-list of column names
   id_t columns;
} create_statement_t;

/**
 * Returns the length of an identifier list
 */
int lengthId(id_t *);

/**
 * Returns the length of a list of numbers
 */
int lengthNum(num_t*);

#ifdef SQL_PARSER_INTERNAL
// CS-525 students don't need to ever call these
id_t* newId(char* id);
num_t* newNum(int num);
condition_t* newCondition(char* left_col, char* op, char* right_col, int num);
select_statement_t* newSelectStatement(id_t* fields, char* table, condition_t* conds);
insert_statement_t* newInsertStatement(char* table, num_t* values);
create_statement_t* newCreateStatement(char* table, id_t* columns);


// CS-525 students don't need to ever call these
void freeId(id_t *);
void freeNum(num_t*);
void freeCondition(condition_t *);
void freeSelectStatement(select_statement_t*);
void freeInsertStatement(insert_statement_t*);
void freeCreateStatement(create_statement_t*);
#endif

#endif
