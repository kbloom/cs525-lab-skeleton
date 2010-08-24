typedef struct id_t{
   char* id;
   struct id_t* next;
} id_t;

id_t* newId(char* id);
int lengthId(id_t *);
void freeId(id_t *);

typedef struct num_t{
   int id;
   struct num_t* next;
} num_t;

num_t* newNum(int num);
int lengthNum(num_t*);
void freeNum(num_t*);

typedef struct condition_t{
   char* left_col;
   char* op;
   char* right_col;
   int right_num;
   struct condition_t* next;
} condition_t;

condition_t* newCondition(char* left_col, char* op, char* right_col, char* num);
void freeCondition(condition_t *);

typedef struct select_statement_t{
   id_t* fields;
   char* table;
   condition_t* conditions;
} select_statement_t;

select_statement_t* newSelectStatement(id_t* fields, char* table, condition_t* conds);
void freeSelectStatement(select_statement_t*);

typedef struct insert_statement_t{
   char* table;
   num_t* values;
} insert_statement_t;

insert_statement_t* newInsertStatement(char* table, num_t* values);
void freeInsertStatement(insert_statement_t*);

typedef struct create_statement_t{
   char* table;
   id_t columns;
} create_statement_t;

create_statement_t* newCreateStatement(char* table, id_t* columns);
void freeCreateStatement(create_statement_t*);
