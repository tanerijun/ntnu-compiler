%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microex.h"

void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

struct symtab symtab[NSYMS];
int symtab_count = 0;
char program_name[256];

int temp_counter = 0;
int label_counter = 0;
struct label_stack if_stack[20];
int if_stack_ptr = 0;
struct label_stack for_stack[20];
int for_stack_ptr = 0;

int in_while_loop = 0;

struct {
    struct symtab *ids[100];
    int count;
    int type;
} current_decl;

struct {
    struct symtab *array;
    struct symtab *index;
} current_array_access;
%}

%union {
    int ival;
    float fval;
    struct symtab *symp;
    struct {
        struct symtab *place;
        int type;
    } expr;
}

%token BEGIN_TOKEN END_TOKEN DECLARE_TOKEN AS_TOKEN INTEGER_TOKEN REAL_TOKEN PROGRAM_TOKEN
%token IF_TOKEN THEN_TOKEN ELSE_TOKEN ENDIF_TOKEN
%token FOR_TOKEN TO_TOKEN DOWNTO_TOKEN ENDFOR_TOKEN STEP_TOKEN
%token WHILE_TOKEN ENDWHILE_TOKEN
%token PRINT_TOKEN WRITE_TOKEN
%token ASSIGN_OP GE_OP LE_OP EQ_OP NE_OP

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <symp> ID

%type <ival> type
%type <expr> expression term factor optional_step
%type <symp> lvalue

%left '+' '-'
%left '*' '/'
%right UMINUS

%start program

%%

program:
    program_header BEGIN_TOKEN stmt_list END_TOKEN
    ;

program_header:
    PROGRAM_TOKEN ID
    {
        strcpy(program_name, $2->name);
        printf("START %s\n", program_name);
    }
    ;

stmt_list:
    stmt
    | stmt_list stmt
    ;

stmt:
    declaration_stmt
    | assignment_stmt
    | if_stmt
    | for_stmt
    | while_stmt
    | print_stmt
    ;

declaration_stmt:
    DECLARE_TOKEN id_list AS_TOKEN type ';'
    {
        for(int i = 0; i < current_decl.count; i++) {
            current_decl.ids[i]->type = $4;
            current_decl.ids[i]->is_declared = 1;

            if (current_decl.ids[i]->isArray) {
                printf("Declare %s, %s_array,%d\n",
                    current_decl.ids[i]->name,
                    $4 == TYPE_INT ? "Integer" : "Float",
                    current_decl.ids[i]->size);
            } else {
                printf("Declare %s, %s\n",
                    current_decl.ids[i]->name,
                    $4 == TYPE_INT ? "Integer" : "Float");
            }
        }
        current_decl.count = 0;
    }
    ;

id_list:
    id_decl
    | id_list ',' id_decl
    ;

id_decl:
    ID
    {
        $1->isArray = 0;
        $1->size = 0;
        current_decl.ids[current_decl.count++] = $1;
    }
    | ID '[' INT_LITERAL ']'
    {
        $1->isArray = 1;
        $1->size = $3;
        current_decl.ids[current_decl.count++] = $1;
    }
    ;

type:
    INTEGER_TOKEN { $$ = TYPE_INT; }
    | REAL_TOKEN  { $$ = TYPE_FLOAT; }
    ;

assignment_stmt:
    lvalue ASSIGN_OP expression ';'
    {
        if (current_array_access.array != NULL) {
            char target_operand_name[100];
            sprintf(target_operand_name, "%s[%s]", current_array_access.array->name, current_array_access.index->name);

            if (current_array_access.array->type == TYPE_INT) {
                if ($3.type == TYPE_INT) {
                    printf("I_Store %s,%s\n", $3.place->name, target_operand_name);
                } else {
                    char *temp_conv = new_temp(TYPE_INT);
                    printf("F_TO_I %s,%s\n", $3.place->name, temp_conv);
                    printf("I_Store %s,%s\n", temp_conv, target_operand_name);
                }
            } else {
                if ($3.type == TYPE_INT) {
                    char *temp_conv = new_temp(TYPE_FLOAT);
                    printf("I_TO_F %s,%s\n", $3.place->name, temp_conv);
                    printf("F_Store %s,%s\n", temp_conv, target_operand_name);
                } else {
                    printf("F_Store %s,%s\n", $3.place->name, target_operand_name);
                }
            }
            current_array_access.array = NULL;
        } else {
            if ($1->type == TYPE_INT) {
                if ($3.type == TYPE_INT) {
                    printf("I_Store %s,%s\n", $3.place->name, $1->name);
                } else {
                    char *temp = new_temp(TYPE_INT);
                    printf("F_TO_I %s,%s\n", $3.place->name, temp);
                    printf("I_Store %s,%s\n", temp, $1->name);
                }
            } else {
                if ($3.type == TYPE_INT) {
                    char *temp = new_temp(TYPE_FLOAT);
                    printf("I_TO_F %s,%s\n", $3.place->name, temp);
                    printf("F_Store %s,%s\n", temp, $1->name);
                } else {
                    printf("F_Store %s,%s\n", $3.place->name, $1->name);
                }
            }
        }
    }
    ;

lvalue:
    ID
    {
        if (!$1->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' not declared.", $1->name);
            yyerror(err_msg);
        }
        $$ = $1;
        current_array_access.array = NULL;
    }
    | ID '[' expression ']'
    {
        if (!$1->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Array '%s' not declared.", $1->name);
            yyerror(err_msg);
        }
        if (!$1->isArray) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' is not an array.", $1->name);
            yyerror(err_msg);
        }
        if ($3.type != TYPE_INT) {
            yyerror("Array index must be an integer.");
        }
        current_array_access.array = $1;
        current_array_access.index = $3.place;
        $$ = $1;
    }
    ;

expression:
    expression '+' term
    {
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        char *temp_res_name;

        if ($$.type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_ADD %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ($1.type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ($3.type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_ADD %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        $$.place = symlook(temp_res_name);
        $$.place->type = $$.type;
    }
    | expression '-' term
    {
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        char *temp_res_name;

        if ($$.type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_SUB %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ($1.type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ($3.type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_SUB %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        $$.place = symlook(temp_res_name);
        $$.place->type = $$.type;
    }
    | term
    {
        $$ = $1;
    }
    ;

term:
    term '*' factor
    {
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        char *temp_res_name;

        if ($$.type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_MUL %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ($1.type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ($3.type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_MUL %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        $$.place = symlook(temp_res_name);
        $$.place->type = $$.type;
    }
    | term '/' factor
    {
        $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        char *temp_res_name;

        if ($$.type == TYPE_INT) {
            temp_res_name = new_temp(TYPE_INT);
            printf("I_DIV %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        } else {
            temp_res_name = new_temp(TYPE_FLOAT);
            if ($1.type == TYPE_INT) {
                char *conv1_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op1_name, conv1_temp);
                op1_name = conv1_temp;
            }
            if ($3.type == TYPE_INT) {
                char *conv2_temp = new_temp(TYPE_FLOAT);
                printf("I_TO_F %s,%s\n", op2_name, conv2_temp);
                op2_name = conv2_temp;
            }
            printf("F_DIV %s,%s,%s\n", op1_name, op2_name, temp_res_name);
        }
        $$.place = symlook(temp_res_name);
        $$.place->type = $$.type;
    }
    | factor
    {
        $$ = $1;
    }
    ;

factor:
    '(' expression ')'
    {
        $$ = $2;
    }
    | '-' factor %prec UMINUS
    {
        $$.type = $2.type;
        char *temp_res_name = new_temp($$.type);
        if ($$.type == TYPE_INT) {
            printf("I_UMINUS %s,%s\n", $2.place->name, temp_res_name);
        } else {
            printf("F_UMINUS %s,%s\n", $2.place->name, temp_res_name);
        }
        $$.place = symlook(temp_res_name);
        $$.place->type = $$.type;
    }
    | INT_LITERAL
    {
        char temp_val[20];
        sprintf(temp_val, "%d", $1);
        struct symtab *s = symlook(temp_val);
        s->type = TYPE_INT;
        s->is_declared = 1;
        $$.place = s;
        $$.type = TYPE_INT;
    }
    | FLOAT_LITERAL
    {
        char temp_val[30];
        sprintf(temp_val, "%f", $1);
        struct symtab *s = symlook(temp_val);
        s->type = TYPE_FLOAT;
        s->is_declared = 1;
        $$.place = s;
        $$.type = TYPE_FLOAT;
    }
    | ID
    {
        if (!$1->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' not declared.", $1->name);
            yyerror(err_msg);
        }
        if ($1->isArray) {
             char err_msg[100];
             sprintf(err_msg, "Array '%s' used without index.", $1->name);
             yyerror(err_msg);
        }
        $$.place = $1;
        $$.type = $1->type;
    }
    | ID '[' expression ']'
    {
        if (!$1->is_declared) {
            char err_msg[100];
            sprintf(err_msg, "Array '%s' not declared.", $1->name);
            yyerror(err_msg);
        }
        if (!$1->isArray) {
            char err_msg[100];
            sprintf(err_msg, "Variable '%s' is not an array, cannot be indexed.", $1->name);
            yyerror(err_msg);
        }
        if ($3.type != TYPE_INT) {
            yyerror("Array index must be an integer expression.");
        }

        char temp_operand_name[100];
        sprintf(temp_operand_name, "%s[%s]", $1->name, $3.place->name);
        struct symtab *s = symlook(temp_operand_name);
        s->type = $1->type;
        s->is_declared = 1;
        $$.place = s;
        $$.type = $1->type;
    }
    ;

if_stmt:
    if_header stmt_list ENDIF_TOKEN
    {
        if_stack_ptr--;
        printf("label_%d:\n", if_stack[if_stack_ptr].begin_label);
    }
    | if_header stmt_list else_part ENDIF_TOKEN
    {
        if_stack_ptr--;
        printf("label_%d:\n", if_stack[if_stack_ptr].end_label);
    }
    ;

if_header:
    IF_TOKEN '('
    {
        if_stack[if_stack_ptr].begin_label = new_label();
        if_stack[if_stack_ptr].end_label = new_label();
        if_stack_ptr++;
    }
    condition ')' THEN_TOKEN
    {
        /* condition rule has already generated the jump to begin_label (else/endif) if false */
    }
    ;

else_part:
    ELSE_TOKEN
    {
        printf("J label_%d\n", if_stack[if_stack_ptr-1].end_label);
        printf("label_%d:\n", if_stack[if_stack_ptr-1].begin_label);
    }
    stmt_list
    ;

for_stmt:
    for_header stmt_list ENDFOR_TOKEN
    {
        char* step_val_str = for_stack[for_stack_ptr-1].step_expr;
        if (step_val_str == NULL) {
            if (for_stack[for_stack_ptr-1].is_downto) {
                printf("DEC %s\n", for_stack[for_stack_ptr-1].var_name);
            } else {
                printf("INC %s\n", for_stack[for_stack_ptr-1].var_name);
            }
        } else {
            if (for_stack[for_stack_ptr-1].is_downto) {
                printf("I_SUB %s,%s,%s\n", for_stack[for_stack_ptr-1].var_name, step_val_str, for_stack[for_stack_ptr-1].var_name);
            } else {
                printf("I_ADD %s,%s,%s\n", for_stack[for_stack_ptr-1].var_name, step_val_str, for_stack[for_stack_ptr-1].var_name);
            }
        }

        printf("I_CMP %s,%s\n", for_stack[for_stack_ptr-1].var_name,
                                        for_stack[for_stack_ptr-1].end_expr);
        if (for_stack[for_stack_ptr-1].is_downto) {
            printf("JGE label_%d\n", for_stack[for_stack_ptr-1].begin_label);
        } else {
            printf("JLE label_%d\n", for_stack[for_stack_ptr-1].begin_label);
        }
        printf("label_%d:\n", for_stack[for_stack_ptr-1].end_label);

        free(for_stack[for_stack_ptr-1].var_name);
        for_stack[for_stack_ptr-1].var_name = NULL;
        free(for_stack[for_stack_ptr-1].end_expr);
        for_stack[for_stack_ptr-1].end_expr = NULL;
        if (for_stack[for_stack_ptr-1].step_expr != NULL) {
            free(for_stack[for_stack_ptr-1].step_expr);
            for_stack[for_stack_ptr-1].step_expr = NULL;
        }
        for_stack_ptr--;
    }
    ;

optional_step:
    /* empty, default step is 1 */
    {
        $$.place = NULL;
        $$.type = TYPE_INT;
    }
    | STEP_TOKEN expression
    {
        if ($2.type != TYPE_INT) {
            yyerror("FOR loop STEP expression must be integer.");
        }
        $$ = $2;
    }
    ;

for_header:
    FOR_TOKEN '(' ID ASSIGN_OP expression TO_TOKEN expression optional_step ')'
    {
        if (!$3->is_declared) { char err_msg[100]; sprintf(err_msg, "Loop variable '%s' not declared.", $3->name); yyerror(err_msg); }
        if ($3->type != TYPE_INT && $3->type != -1) { yyerror("Loop variable must be an integer."); }
        if ($5.type != TYPE_INT) { yyerror("FOR loop start expression must be integer.");}
        if ($7.type != TYPE_INT) { yyerror("FOR loop end expression must be integer.");}
        $3->type = TYPE_INT;

        printf("I_Store %s,%s\n", $5.place->name, $3->name);

        for_stack[for_stack_ptr].begin_label = new_label();
        for_stack[for_stack_ptr].end_label = new_label();
        for_stack[for_stack_ptr].var_name = strdup($3->name);
        for_stack[for_stack_ptr].end_expr = strdup($7.place->name);
        if ($8.place != NULL) { // $8 is optional_step
            for_stack[for_stack_ptr].step_expr = strdup($8.place->name);
        } else {
            for_stack[for_stack_ptr].step_expr = NULL; // Explicitly mark no custom step
        }
        for_stack[for_stack_ptr].is_downto = 0;

        printf("label_%d:\n", for_stack[for_stack_ptr].begin_label);
        printf("I_CMP %s,%s\n", $3->name, for_stack[for_stack_ptr].end_expr);
        printf("JG label_%d\n", for_stack[for_stack_ptr].end_label);

        for_stack_ptr++;
    }
    | FOR_TOKEN '(' ID ASSIGN_OP expression DOWNTO_TOKEN expression optional_step ')'
    {
        if (!$3->is_declared) { char err_msg[100]; sprintf(err_msg, "Loop variable '%s' not declared.", $3->name); yyerror(err_msg); }
        if ($3->type != TYPE_INT && $3->type != -1) { yyerror("Loop variable must be an integer."); }
        if ($5.type != TYPE_INT) { yyerror("FOR loop start expression must be integer.");}
        if ($7.type != TYPE_INT) { yyerror("FOR loop end expression must be integer.");}
        $3->type = TYPE_INT;

        printf("I_Store %s,%s\n", $5.place->name, $3->name);

        for_stack[for_stack_ptr].begin_label = new_label();
        for_stack[for_stack_ptr].end_label = new_label();
        for_stack[for_stack_ptr].var_name = strdup($3->name);
        for_stack[for_stack_ptr].end_expr = strdup($7.place->name);
        if ($8.place != NULL) { // $8 is optional_step
            for_stack[for_stack_ptr].step_expr = strdup($8.place->name);
        } else {
            for_stack[for_stack_ptr].step_expr = NULL;
        }
        for_stack[for_stack_ptr].is_downto = 1;

        printf("label_%d:\n", for_stack[for_stack_ptr].begin_label);
        printf("I_CMP %s,%s\n", $3->name, for_stack[for_stack_ptr].end_expr);
        printf("JL label_%d\n", for_stack[for_stack_ptr].end_label);

        for_stack_ptr++;
    }
    ;

while_stmt:
    while_header stmt_list ENDWHILE_TOKEN
    {
        printf("J label_%d\n", if_stack[if_stack_ptr-1].begin_label);
        printf("label_%d:\n", if_stack[if_stack_ptr-1].end_label);
        if_stack_ptr--;
    }
    ;

while_header:
    WHILE_TOKEN '('
    {
        if_stack[if_stack_ptr].begin_label = new_label();
        if_stack[if_stack_ptr].end_label = new_label();
        if_stack_ptr++;
        printf("label_%d:\n", if_stack[if_stack_ptr-1].begin_label);
        in_while_loop = 1;
    }
    condition ')'
    {
        in_while_loop = 0;
    }
    ;

condition:
    expression '>' expression
    {
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ($1.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ($3.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JLE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    }
    | expression '<' expression
    {
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ($1.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ($3.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JGE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    }
    | expression GE_OP expression
    {
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ($1.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ($3.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JL label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    }
    | expression LE_OP expression
    {
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ($1.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ($3.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JG label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    }
    | expression EQ_OP expression
    {
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ($1.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ($3.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JNE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    }
    | expression NE_OP expression
    {
        char *op1_name = $1.place->name;
        char *op2_name = $3.place->name;
        if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
            printf("I_CMP %s,%s\n", op1_name, op2_name);
        } else {
            if ($1.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op1_name, conv_temp); op1_name = conv_temp; }
            if ($3.type == TYPE_INT) { char *conv_temp = new_temp(TYPE_FLOAT); printf("I_TO_F %s,%s\n", op2_name, conv_temp); op2_name = conv_temp; }
            printf("F_CMP %s,%s\n", op1_name, op2_name);
        }
        printf("JE label_%d\n", in_while_loop ? if_stack[if_stack_ptr-1].end_label : if_stack[if_stack_ptr-1].begin_label);
    }
    | '(' condition ')'
    ;

print_stmt:
    PRINT_TOKEN '(' print_list ')' ';'
    | WRITE_TOKEN '(' print_list ')' ';'
    ;

print_list:
    expression
    {
        printf("CALL print, %s\n", $1.place->name);
    }
    | print_list ',' expression
    {
        printf("CALL print, %s\n", $3.place->name);
    }
    ;

%%

struct symtab *symlook(char *s) {
    for(int i = 0; i < symtab_count; i++) {
        if(strcmp(symtab[i].name, s) == 0) {
            return &symtab[i];
        }
    }

    if(symtab_count >= NSYMS) {
        fprintf(stderr, "Symbol table full, too many symbols (max %d)\n", NSYMS);
        exit(1);
    }

    symtab[symtab_count].name = strdup(s);
    symtab[symtab_count].is_declared = 0;
    symtab[symtab_count].isArray = 0;
    symtab[symtab_count].size = 0;
    symtab[symtab_count].type = -1;
    return &symtab[symtab_count++];
}

char *new_temp(int type) {
    char name_buf[20];
    sprintf(name_buf, "T&%d", ++temp_counter);
    struct symtab *s = symlook(name_buf);
    s->type = type;
    s->is_declared = 1;
    s->isArray = 0;
    s->size = 0;
    return s->name;
}

int new_label() {
    return ++label_counter;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
    exit(1);
}

int main(int argc, char* argv[]) {
    memset(symtab, 0, sizeof(symtab));
    symtab_count = 0;
    current_decl.count = 0;
    temp_counter = 0;
    label_counter = 0;
    if_stack_ptr = 0;
    for_stack_ptr = 0;
    program_name[0] = '\0';


    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    int result = yyparse();

    if(result == 0) {
        printf("HALT %s\n", program_name[0] == '\0' ? "DefaultProgram" : program_name);

        for(int i = 0; i < symtab_count; i++) { /* iterate all symbols to find temporaries */
            if (symtab[i].name[0] == 'T' && symtab[i].name[1] == '&') {
                 if (symtab[i].type != -1) {
                    printf("Declare %s, %s\n", symtab[i].name,
                        symtab[i].type == TYPE_INT ? "Integer" : "Float");
                 }
            }
        }
    } else {
        fprintf(stderr, "\nParsing failed.\n");
    }

    if (yyin != stdin && yyin != NULL) {
        fclose(yyin);
    }

    return result;
}
