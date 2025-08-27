
%code requires {
typedef struct { int *vals; int count; } IntList;
}
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

// Forward declarations
struct Expression;
struct Statement;
int evaluateExpression(struct Expression* e);


/* --- NEW: Expression Tree Structure --- */
// Represents a calculation that can be evaluated later.
typedef struct Expression {
    enum { EXPR_CONST, EXPR_VAR, EXPR_ARRAY_ACCESS, EXPR_BINOP, EXPR_UNOP, EXPR_STRLEN_VAR, EXPR_STRLEN_LIT } kind;
    int op; // The operator for BINOP/UNOP (e.g., PLUS, MINUS)
    struct Expression *left;
    struct Expression *right;
    int value;
    char name[50];
    char* str_literal;
} Expression;


/* Symbol table */
#define MAX_SYMBOLS 100
typedef struct {
    char name[50];
    int intValue;
    char* strValue;
    int type;      // 0=int, 1=char, 2=string, 3=array
    int array_values[100];
    int array_size;
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

/* --- MODIFIED: Statement structure --- */
typedef struct Statement {
    enum { STMT_SHOW, STMT_ASSIGN, STMT_EXPR, STMT_ASSIGN_STR, STMT_ASSIGN_CHAR, STMT_ARRAY_ASSIGN, STMT_IF, STMT_WHILE, STMT_SWAP } kind;
    char varName[50];
    struct Expression* value_expr; // For conditions, assignments, array indices etc.
    char* strValue;                // For string literal assignments
    struct Statement* body;        // For if/while
    struct Statement* else_body;   // For if-else
    struct Statement* next;
    char swapVar2[50]; // For SWAP statement: second variable name
} Statement;

/* Function table */
#define MAX_FUNCTIONS 50
typedef struct {
    char name[50];
    Statement* body;
} Function;

Function funcTable[MAX_FUNCTIONS];
int funcCount = 0;

/* Function prototypes */
int findSymbolIndex(char* name);
void addSymbol(char* name,int intVal,char* strVal,int type);
void addFunction(char* name, Statement* body);
void executeFunction(char* name);
void executeStatement(Statement* s);
char* value_to_unquoted_string_from_identifier(const char* name);
char* strip_quotes(const char* s);
char* concat_and_quote(const char* a, const char* b);
Expression* new_const_node(int val);
Expression* new_var_node(char* name);
Expression* new_array_access_node(char* name, Expression* index_expr);
Expression* new_op_node(int op, Expression* left, Expression* right);
Expression* new_strlen_var_node(char* name);
Expression* new_strlen_lit_node(char* literal);

%}

/* --- MODIFIED: %union --- */
%union {
    int num;
    char* str;
    struct Statement* stmt;
    struct Expression* expr; // Added to hold expression trees
    IntList* ilist;
}

%token MYTYPE SHOW SWAP FUNCTION RETURN STRLEN CONCAT INTTYPE FLOATTYPE CHARTYPE STRINGTYPE IF ELSE WHILE ARRAYTYPE
%token <str> IDENTIFIER STRING_LITERAL CHAR_LITERAL
%token <num> NUMBER
%token PLUS MINUS TIMES DIVIDE
%token AND OR NOT
%token BAND BOR BXOR BNOT LSHIFT RSHIFT
%token EQ NE GE LE

%left OR
%left AND
%right NOT
%left BOR
%left BXOR
%left BAND
%left LSHIFT RSHIFT
%left PLUS MINUS
%left TIMES DIVIDE
%left '>' '<'
%left EQ NE GE LE
%right BNOT
%left UMINUS

%expect 3

/* --- MODIFIED: %type --- */
%type <expr> expression
%type <stmt> statement block statements statements_in_func statement_in_func declaration_list
%type <num> type_spec
%type <ilist> expr_list

%%

program:
    statements
;

/* ---------- GLOBAL STATEMENTS (immediate execution) ---------- */
statements:
      statements statement { if($2) executeStatement($2); free($2); }
    | statement { if($1) executeStatement($1); free($1); }
;

statement:
      type_spec declaration_list ';' { $$=NULL; }
    | IDENTIFIER '=' expression ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN;
          strcpy(s->varName,$1);
          s->value_expr=$3;
          s->next=NULL;
          $$=s;
      }
    /* --- NEW: WHILE loop rule --- */
    | WHILE '(' expression ')' block {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_WHILE;
          s->value_expr = $3; // Store the condition expression tree
          s->body = $5;
          s->else_body = NULL;
          s->next = NULL;
          $$ = s;
      }
    | IF '(' expression ')' block { 
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = $3; // Store the condition expression tree
          s->body = $5;
          s->else_body = NULL;
          s->next = NULL;
          $$ = s;
      }
    | IF '(' expression ')' block ELSE block {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = $3; // Store the condition expression tree
          s->body = $5;
          s->else_body = $7;
          s->next = NULL;
          $$ = s;
      }
    | IDENTIFIER '[' expression ']' '=' expression ';' {
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_ARRAY_ASSIGN;
        strcpy(s->varName,$1);
        s->value_expr = new_op_node(0, $3, $6); // Use op node to hold index and value
        s->next = NULL;
        $$ = s;
      }
    | IDENTIFIER '=' STRING_LITERAL ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_STR;
          strcpy(s->varName,$1);
          s->strValue=strdup($3);
          s->next=NULL;
          $$=s;
      }
    | IDENTIFIER '=' IDENTIFIER CONCAT IDENTIFIER ';' {
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_ASSIGN_STR;
        strcpy(s->varName,$1);
        char* left = value_to_unquoted_string_from_identifier($3);
        char* right = value_to_unquoted_string_from_identifier($5);
        char* res = concat_and_quote(left,right);
        s->strValue = res;
        s->next = NULL;
        if(left) free(left);
        if(right) free(right);
        $$ = s;
      }
    | IDENTIFIER '=' CHAR_LITERAL ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_CHAR;
          strcpy(s->varName,$1);
          s->strValue = strdup($3); // Store full literal e.g. 'c'
          s->next=NULL;
          $$=s;
      }
    | SHOW '(' IDENTIFIER ')' ';' {
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_SHOW;
        strcpy(s->varName,$3);
        s->next=NULL;
        $$=s;
      }
    | SHOW '(' expression ')' ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_EXPR;
          s->value_expr = $3;
          s->next = NULL;
          $$ = s;
      }
        | SWAP '(' IDENTIFIER ',' IDENTIFIER ')' ';' {
                Statement* s = malloc(sizeof(Statement));
                s->kind = STMT_SWAP;
                strcpy(s->varName, $3);
                strcpy(s->swapVar2, $5);
                s->next = NULL;
                $$ = s;
            }
    | FUNCTION IDENTIFIER '(' ')' block { 
        addFunction($2,$5); 
        printf("Function %s defined.\n",$2); 
        $$=NULL;
      }
    | IDENTIFIER '(' ')' ';' { 
        executeFunction($1); 
        $$=NULL;
      }
    | expression ';' { 
        Statement* s = malloc(sizeof(Statement));
        s->kind = STMT_EXPR;
        s->value_expr = $1;
        s->next=NULL;
        $$=s;
      }
;

/* ---------- FUNCTION BODY (store only, no execution) ---------- */
block:
      '{' statements_in_func '}' { $$=$2; }
    | statement_in_func { $$=$1; }
;

statements_in_func:
      statements_in_func statement_in_func { 
          if($1) {
              Statement* t = $1;
              while(t->next) t=t->next;
              t->next = $2;
              $$ = $1;
          } else $$=$2;
      }
    | statement_in_func { $$=$1; }
;

statement_in_func:
      IDENTIFIER '=' expression ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN;
          strcpy(s->varName,$1);
          s->value_expr=$3;
          s->next=NULL;
          $$=s;
      }
    /* --- NEW: WHILE loop rule for functions --- */
    | WHILE '(' expression ')' block {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_WHILE;
          s->value_expr = $3;
          s->body = $5;
          s->else_body = NULL;
          s->next = NULL;
          $$ = s;
      }
    | IF '(' expression ')' block { 
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = $3;
          s->body = $5;
          s->else_body = NULL;
          s->next = NULL;
          $$ = s;
      }
    | IF '(' expression ')' block ELSE block {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_IF;
          s->value_expr = $3;
          s->body = $5;
          s->else_body = $7;
          s->next = NULL;
          $$ = s;
      }
    | IDENTIFIER '=' STRING_LITERAL ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_STR;
          strcpy(s->varName,$1);
          s->strValue=strdup($3);
          s->next=NULL;
          $$=s;
      }
    | IDENTIFIER '=' IDENTIFIER CONCAT IDENTIFIER ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_STR;
          strcpy(s->varName,$1);
          char* left = value_to_unquoted_string_from_identifier($3);
          char* right = value_to_unquoted_string_from_identifier($5);
          s->strValue = concat_and_quote(left,right);
          s->next=NULL;
          if(left) free(left);
          if(right) free(right);
          $$=s;
      }
    | IDENTIFIER '=' CHAR_LITERAL ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_ASSIGN_CHAR;
          strcpy(s->varName,$1);
          s->strValue = strdup($3);
          s->next=NULL;
          $$=s;
      }
    | SHOW '(' IDENTIFIER ')' ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_SHOW;
          strcpy(s->varName,$3);
          s->next=NULL;
          $$=s;
      }
    | SHOW '(' expression ')' ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_EXPR;
          s->value_expr = $3;
          s->next = NULL;
          $$ = s;
      }
    | expression ';' {
          Statement* s = malloc(sizeof(Statement));
          s->kind = STMT_EXPR;
          s->value_expr = $1;
          s->next=NULL;
          $$=s;
      }
        | SWAP '(' IDENTIFIER ',' IDENTIFIER ')' ';' {
                Statement* s = malloc(sizeof(Statement));
                s->kind = STMT_SWAP;
                strcpy(s->varName, $3);
                strcpy(s->swapVar2, $5);
                s->next = NULL;
                $$ = s;
            }
;

/* ---------- DECLARATIONS ---------- */
declaration_list:
            IDENTIFIER { addSymbol($1,0,NULL,0); printf("Declared %s as int with default 0\n",$1); }
        | IDENTIFIER '=' expression { int val=evaluateExpression($3); addSymbol($1,val,NULL,0); printf("Declared %s with value %d\n",$1,val); free($3); }
        | IDENTIFIER '[' NUMBER ']' { addSymbol($1,$3,NULL,3); printf("Declared %s as array of size %d\n",$1,$3); }
        | IDENTIFIER '=' '{' expr_list '}' { 
                    IntList* il = $4;
                    addSymbol($1, il->count, NULL, 3);
                    int idx = findSymbolIndex($1);
                    if(idx != -1){
                            for(int i=0;i<il->count;i++) symbolTable[idx].array_values[i]=il->vals[i];
                    }
                    printf("Declared %s as array with initializer (size %d)\n",$1, il->count);
                    free(il->vals); free(il);
            }
        | IDENTIFIER '=' STRING_LITERAL { addSymbol($1,0,$3,2); printf("Declared %s as string with value '%s'\n",$1,$3); }
        | IDENTIFIER '=' CHAR_LITERAL { addSymbol($1,$3[1],NULL,1); printf("Declared %s as char with value '%c'\n",$1,$3[1]); }
        | declaration_list ',' IDENTIFIER { addSymbol($3,0,NULL,0); printf("Declared %s as int with default 0\n",$3); }
        | declaration_list ',' IDENTIFIER '=' expression { int val=evaluateExpression($5); addSymbol($3,val,NULL,0); printf("Declared %s with value %d\n",$3,val); free($5); }
        | declaration_list ',' IDENTIFIER '[' NUMBER ']' { addSymbol($3,$5,NULL,3); printf("Declared %s as array of size %d\n",$3,$5); }
    | declaration_list ',' IDENTIFIER '=' '{' expr_list '}' { 
            IntList* il = $6;
            addSymbol($3, il->count, NULL, 3);
            int idx = findSymbolIndex($3);
            if(idx != -1){
                for(int i=0;i<il->count;i++) symbolTable[idx].array_values[i]=il->vals[i];
            }
            printf("Declared %s as array with initializer (size %d)\n",$3, il->count);
            free(il->vals); free(il);
        }
    | declaration_list ',' IDENTIFIER '=' STRING_LITERAL { addSymbol($3,0,$5,2); printf("Declared %s as string with value '%s'\n",$3,$5); }
    | declaration_list ',' IDENTIFIER '=' CHAR_LITERAL { addSymbol($3,$5[1],NULL,1); printf("Declared %s as char with value '%c'\n",$3,$5[1]); }
;

type_spec:
      MYTYPE { $$ = 0; }
    | INTTYPE { $$ = 0; }
    | FLOATTYPE { $$ = 4; }
    | CHARTYPE { $$ = 1; }
    | STRINGTYPE { $$ = 2; }
;

expr_list:
      expr_list ',' expression {
          IntList* t = $1;
          t->vals = realloc(t->vals, (t->count+1)*sizeof(int));
          t->vals[t->count] = evaluateExpression($3); t->count++; $$ = t; free($3); }
    | expression { IntList* t = malloc(sizeof(IntList)); t->vals = malloc(sizeof(int)); t->vals[0] = evaluateExpression($1); t->count = 1; $$ = t; free($1); }
;

/* --- MODIFIED: expression rules now build an expression tree --- */
expression:
      STRLEN '(' IDENTIFIER ')'         { $$ = new_strlen_var_node($3); }
    | STRLEN '(' STRING_LITERAL ')'   { $$ = new_strlen_lit_node($3); }
    | expression '>' expression       { $$ = new_op_node('>', $1, $3); }
    | expression '<' expression       { $$ = new_op_node('<', $1, $3); }
    | expression EQ expression        { $$ = new_op_node(EQ, $1, $3); }
    | expression NE expression        { $$ = new_op_node(NE, $1, $3); }
    | expression GE expression        { $$ = new_op_node(GE, $1, $3); }
    | expression LE expression        { $$ = new_op_node(LE, $1, $3); }
    | expression AND expression       { $$ = new_op_node(AND, $1, $3); }
    | expression OR expression        { $$ = new_op_node(OR, $1, $3); }
    | NOT expression                  { $$ = new_op_node(NOT, $2, NULL); }
    | expression PLUS expression      { $$ = new_op_node(PLUS, $1, $3); }
    | expression MINUS expression     { $$ = new_op_node(MINUS, $1, $3); }
    | expression TIMES expression     { $$ = new_op_node(TIMES, $1, $3); }
    | expression DIVIDE expression    { $$ = new_op_node(DIVIDE, $1, $3); }
    | NUMBER                          { $$ = new_const_node($1); }
    | IDENTIFIER                      { $$ = new_var_node($1); }
    | IDENTIFIER '[' expression ']'   { $$ = new_array_access_node($1, $3); }
    | '(' expression ')'              { $$ = $2; }
;

%%

void yyerror(const char *s){ fprintf(stderr,"Error: %s\n",s); }
int main(){ return yyparse(); }

/* --- NEW: Expression Tree Node Constructors --- */
Expression* new_const_node(int val) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_CONST; e->value = val;
    return e;
}
Expression* new_var_node(char* name) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_VAR; strcpy(e->name, name);
    return e;
}
Expression* new_array_access_node(char* name, Expression* index_expr) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_ARRAY_ACCESS;
    strcpy(e->name, name);
    e->left = index_expr;
    e->right = NULL;
    return e;
}
Expression* new_op_node(int op, Expression* left, Expression* right) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = right ? EXPR_BINOP : EXPR_UNOP;
    e->op = op; e->left = left; e->right = right;
    return e;
}
Expression* new_strlen_var_node(char* name) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_STRLEN_VAR; strcpy(e->name, name);
    return e;
}
Expression* new_strlen_lit_node(char* literal) {
    Expression* e = malloc(sizeof(Expression));
    e->kind = EXPR_STRLEN_LIT; e->str_literal = strdup(literal);
    return e;
}

/* --- NEW: Expression Tree Evaluator --- */
int evaluateExpression(Expression* e) {
    if (!e) return 0;
    switch (e->kind) {
        case EXPR_CONST: return e->value;
        case EXPR_VAR: {
            int idx = findSymbolIndex(e->name);
            if (idx == -1) { printf("Error: %s not declared\n", e->name); return 0; }
            return symbolTable[idx].intValue;
        }
        case EXPR_ARRAY_ACCESS: {
            int idx = findSymbolIndex(e->name);
            if(idx==-1){printf("Error: %s not declared\n",e->name);return 0;}
            int i = evaluateExpression(e->left);
            if(i<0 || i>=symbolTable[idx].array_size){printf("Index out of bounds for %s\n",e->name); return 0;}
            return symbolTable[idx].array_values[i];
        }
        case EXPR_STRLEN_VAR: {
            int idx = findSymbolIndex(e->name);
            if (idx == -1) { printf("Error: %s not declared\n", e->name); return 0; }
            if(symbolTable[idx].type == 2 && symbolTable[idx].strValue) {
                char* str = symbolTable[idx].strValue;
                size_t len = strlen(str);
                if(len >= 2 && str[0] == '"' && str[len-1] == '"') return (int)(len-2);
                return (int)len;
            } else if (symbolTable[idx].type == 1) { return 1; }
            return 0;
        }
        case EXPR_STRLEN_LIT: {
            char* s = e->str_literal;
            size_t len = strlen(s);
            if(len >= 2 && s[0] == '"' && s[len-1] == '"') return (int)(len-2);
            return (int)len;
        }
        case EXPR_UNOP:
            if (e->op == NOT) return !evaluateExpression(e->left);
            return 0; // Other unary ops can be added here
        case EXPR_BINOP: {
            int left_val = evaluateExpression(e->left);
            int right_val = evaluateExpression(e->right);
            switch (e->op) {
                case PLUS: return left_val + right_val;
                case MINUS: return left_val - right_val;
                case TIMES: return left_val * right_val;
                case DIVIDE: if(right_val==0){yyerror("Division by zero");return 0;} return left_val/right_val;
                case '>': return left_val > right_val;
                case '<': return left_val < right_val;
                case EQ: return left_val == right_val;
                case NE: return left_val != right_val;
                case GE: return left_val >= right_val;
                case LE: return left_val <= right_val;
                case AND: return left_val && right_val;
                case OR: return left_val || right_val;
                default: return 0;
            }
        }
    }
    return 0;
}

/* ---------- SYMBOL FUNCTIONS ---------- */
int findSymbolIndex(char* name){ 
    for(int i=0;i<symbolCount;i++) 
        if(strcmp(symbolTable[i].name,name)==0) return i; 
    return -1; 
}
void addSymbol(char* name,int intVal,char* strVal,int type){
    int idx=findSymbolIndex(name);
    if(idx==-1){ 
        strcpy(symbolTable[symbolCount].name,name); 
        symbolTable[symbolCount].intValue=intVal; 
        symbolTable[symbolCount].strValue=strVal?strdup(strVal):NULL; 
        symbolTable[symbolCount].type=type; 
        symbolTable[symbolCount].array_size = (type==3)?intVal:0;
        symbolCount++; 
    }
    else{ 
        symbolTable[idx].intValue=intVal; 
        if(symbolTable[idx].strValue) free(symbolTable[idx].strValue); 
        symbolTable[idx].strValue=strVal?strdup(strVal):NULL; 
        symbolTable[idx].type=type; 
        if(type==3) symbolTable[idx].array_size = intVal;
    }
}

/* --- MODIFIED: Statement Executor --- */
void executeStatement(Statement* s) {
    if(!s) return;
    switch(s->kind) {
        case STMT_ASSIGN: {
            int val = evaluateExpression(s->value_expr);
            addSymbol(s->varName, val, NULL, 0);
            printf("Assigned %d to %s\n", val, s->varName);
            break;
        }
        case STMT_ASSIGN_STR: {
            addSymbol(s->varName, 0, s->strValue, 2);
            printf("Assigned string %s to %s\n", s->strValue, s->varName);
            break;
        }
        case STMT_ASSIGN_CHAR: {
            addSymbol(s->varName, s->strValue[1], NULL, 1);
            printf("Assigned char '%c' to %s\n", s->strValue[1], s->varName);
            break;
        }
        case STMT_ARRAY_ASSIGN: {
            int idx_val = evaluateExpression(s->value_expr->left);
            int val = evaluateExpression(s->value_expr->right);
            int sym_idx = findSymbolIndex(s->varName);
            if(sym_idx == -1) { printf("Error: %s not declared\n", s->varName); }
            else if(symbolTable[sym_idx].type != 3) { printf("Error: %s is not an array\n", s->varName); }
            else if(idx_val < 0 || idx_val >= symbolTable[sym_idx].array_size) { printf("Index out of bounds for %s\n", s->varName); }
            else { symbolTable[sym_idx].array_values[idx_val] = val; printf("Assigned %d to %s[%d]\n", val, s->varName, idx_val); }
            break;
        }
        case STMT_SHOW: {
            int idx=findSymbolIndex(s->varName);
            if(idx!=-1){
                if(symbolTable[idx].type==0) printf("%s=%d\n",s->varName,symbolTable[idx].intValue);
                else if(symbolTable[idx].type==1) printf("%s='%c'\n",s->varName,(char)symbolTable[idx].intValue);
                else if(symbolTable[idx].type==2 && symbolTable[idx].strValue) printf("%s=%s\n",s->varName, symbolTable[idx].strValue);
                else printf("%s=<unknown type>\n",s->varName);
            } else printf("Variable %s not declared\n",s->varName);
            break;
        }
        case STMT_EXPR: {
            printf("Expression result: %d\n", evaluateExpression(s->value_expr));
            break;
        }
        case STMT_SWAP: {
            int idx1 = findSymbolIndex(s->varName);
            int idx2 = findSymbolIndex(s->swapVar2);
            if(idx1 == -1 || idx2 == -1) {
                printf("Error: variable(s) not declared\n");
                break;
            }
            if(symbolTable[idx1].type != symbolTable[idx2].type) {
                printf("Error: type mismatch for swap\n");
                break;
            }
            switch(symbolTable[idx1].type) {
                case 0: // int
                case 4: // float (if supported)
                    {
                        int tmp = symbolTable[idx1].intValue;
                        symbolTable[idx1].intValue = symbolTable[idx2].intValue;
                        symbolTable[idx2].intValue = tmp;
                        printf("Swapped %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                case 1: // char
                    {
                        int tmp = symbolTable[idx1].intValue;
                        symbolTable[idx1].intValue = symbolTable[idx2].intValue;
                        symbolTable[idx2].intValue = tmp;
                        printf("Swapped chars %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                case 2: // string
                    {
                        char* tmp = symbolTable[idx1].strValue;
                        symbolTable[idx1].strValue = symbolTable[idx2].strValue;
                        symbolTable[idx2].strValue = tmp;
                        printf("Swapped strings %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                case 3: // array
                    {
                        int* tmp = malloc(sizeof(int)*symbolTable[idx1].array_size);
                        memcpy(tmp, symbolTable[idx1].array_values, sizeof(int)*symbolTable[idx1].array_size);
                        memcpy(symbolTable[idx1].array_values, symbolTable[idx2].array_values, sizeof(int)*symbolTable[idx1].array_size);
                        memcpy(symbolTable[idx2].array_values, tmp, sizeof(int)*symbolTable[idx1].array_size);
                        free(tmp);
                        printf("Swapped arrays %s and %s\n", s->varName, s->swapVar2);
                    }
                    break;
                default:
                    printf("Swap not supported for this type\n");
            }
            break;
        }
        case STMT_IF: {
            if (evaluateExpression(s->value_expr)) {
                Statement* t = s->body;
                while(t) { executeStatement(t); t = t->next; }
            } else if (s->else_body) {
                Statement* t = s->else_body;
                while(t) { executeStatement(t); t = t->next; }
            }
            break;
        }
        /* --- NEW: WHILE loop execution logic --- */
        case STMT_WHILE: {
            while (evaluateExpression(s->value_expr)) {
                Statement* t = s->body;
                while (t) {
                    executeStatement(t);
                    t = t->next;
                }
            }
            break;
        }
    }
}

/* ---------- FUNCTION SUPPORT ---------- */
int findFunctionIndex(char* name){ 
    for(int i=0;i<funcCount;i++) 
        if(strcmp(funcTable[i].name,name)==0) return i; 
    return -1; 
}
void addFunction(char* name, Statement* body){ 
    strcpy(funcTable[funcCount].name,name); 
    funcTable[funcCount].body=body; 
    funcCount++; 
}
void executeFunction(char* name){
    int idx=findFunctionIndex(name);
    if(idx==-1){ printf("Error: function %s not found\n",name); return; }
    Statement* s=funcTable[idx].body;
    printf("Executing function %s\n",name);
    while(s){
        executeStatement(s);
        s=s->next;
    }
}

/* ---------- STRING HELPERS ---------- */
char* strip_quotes(const char* s){
    if(!s) return NULL;
    size_t len = strlen(s);
    if(len >= 2 && s[0] == '"' && s[len-1] == '"'){
        char* out = malloc(len-1);
        strncpy(out, s+1, len-2);
        out[len-2] = '\0';
        return out;
    }
    return strdup(s);
}

char* concat_and_quote(const char* a, const char* b){
    const char* aa = a?a:"";
    const char* bb = b?b:"";
    size_t la = strlen(aa);
    size_t lb = strlen(bb);
    char* out = malloc(la+lb+3);
    out[0] = '"';
    memcpy(out+1, aa, la);
    memcpy(out+1+la, bb, lb);
    out[1+la+lb] = '"';
    out[1+la+lb+1] = '\0';
    return out;
}

char* value_to_unquoted_string_from_identifier(const char* name){
    int idx = findSymbolIndex((char*)name);
    if(idx == -1) return strdup("");
    if(symbolTable[idx].type == 2 && symbolTable[idx].strValue){
        return strip_quotes(symbolTable[idx].strValue);
    }
    if(symbolTable[idx].type == 1){
        char buf[2] = {(char)symbolTable[idx].intValue, '\0'};
        return strdup(buf);
    }
    if(symbolTable[idx].type == 0){
        char tmp[64];
        sprintf(tmp, "%d", symbolTable[idx].intValue);
        return strdup(tmp);
    }
    return strdup("");
}
