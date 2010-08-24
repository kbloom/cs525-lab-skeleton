#ifndef AST_H
#define AST_H

/**
 * A singly linked-list of identifiers (either table names or column names)
 */
typedef struct id_list_t{
   char* id;
   struct id_list_t* next;
} id_list_t;

/**
 * A singly-linked list of numbers.
 */
typedef struct num_list_t{
   int num;
   struct num_list_t* next;
} num_list_t;


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
   id_list_t* fields;
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
   num_list_t* values;
} insert_statement_t;


/**
 * This holds all of the information that was in a CREATE TABLE statement.
 */
typedef struct create_statement_t{
   /// the name of the table to create
   char* table;
   /// a singly-list of column names
   id_list_t* columns;
} create_statement_t;

/**
 *  This enum defines a bunch of commands that take no parameters.
 *  If the parser found some command not listed here, then the type
 *  CMD_NONE is used to indicate that none of the parameterless commands should
 *  be run.
 */
typedef enum parameterless_statement_t{
   CMD_NONE=0,
   CMD_PRINT_CATALOG,
   CMD_PRINT_BUFFER,
   CMD_PRINT_HIT_RATE,
   CMD_COMMIT,
   CMD_EXIT
} parameterless_statement_t;

enum variable_t{
   CONFIG_TIMER
};

typedef enum variable_t variable_t;

typedef struct set_statement_t{
   variable_t variable;
   //value is a boolean -- 0 means "off" and nonzero means "on"
   int value;
} set_statement_t;

typedef struct statement_t{
   select_statement_t* select;
   create_statement_t* createTable;
   insert_statement_t* insert;
   char* dropTable;   
   char* printTable;
   set_statement_t* set;
   parameterless_statement_t parameterless;
} statement_t;


/**
 * Returns the length of an identifier list
 */
int lengthIdList(const id_list_t *);

/**
 * Returns the length of a list of numbers
 */
int lengthNumList(const num_list_t*);

/**
 * Frees a parsed SQL statement, and all of the objects created inside it.
 * This includes all strings created in side it. If you want to use them persistently,
 * you call strdup() on them (or copy them to a std::string) and save the duplicate.
 */
void freeStatement(statement_t* stmt);

/**
 * This is the main entry point for the parser 
 */
statement_t * parseStatement(char * stmt);

#ifdef SQL_PARSER_INTERNAL
// CS-525 students don't need to ever call these
id_list_t* newIdList(char* id);
num_list_t* newNumList(int num);
condition_t* newCondition(char* left_col, char* op, char* right_col, int num);
select_statement_t* newSelectStatement(id_list_t* fields, char* table, condition_t* conds);
insert_statement_t* newInsertStatement(char* table, num_list_t* values);
create_statement_t* newCreateStatement(char* table, id_list_t* columns);
set_statement_t* newSetStatement(variable_t variable, int value);
statement_t* newStatement(void);

// CS-525 students don't need to ever call these
void freeIdList(id_list_t *);
void freeNumList(num_list_t*);
void freeCondition(condition_t *);
void freeSelectStatement(select_statement_t*);
void freeInsertStatement(insert_statement_t*);
void freeCreateStatement(create_statement_t*);
void freeSetStatement(set_statement_t*);

// the statement returned by parsing a single line of SQL
extern statement_t* returned_statement;
#endif

#endif
