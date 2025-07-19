# Micro/Ex Compiler - Final Project Report

**Course:** Compiler Design

**Student Name:** 陳偉俊

**Student ID:** 61347090S

## 1. Introduction

This report list the features I implemented in my Micro/Ex compiler. The compiler is built using Lex and Yacc. It translates Micro/Ex source code into a three-address code representation as defined by professor in his slide `Final Project 說明`. Each functionality is demonstrated by showing its output on its corresponding test case.

## 2. Implemented Features

Below are the implemented features:

> Note that the test cases below are excerpt of the full test case. The full test cases are available in the `test` directory.

### 2.1. Basic Structure and Declarations

The compiler handles the basic program structure (`Program <name>`, `Begin`, `End`) and variable declarations for integers, floats (reals), and arrays of these types. The compiler also supports case insensitivity for keywords (identifiers are still case-sensitive).

> Note that variables must be declared before use, else the compiler will throw an "undefined variable" error.

**Test Case (`01_declaration.microex`):**

```microex
%%Test for variable declarations
Program DeclTest
Begin
  declare a, b, c as integer;
  declare x, y, z[10] as real;
end
```

**Generated Assembly:**

```assembly
START DeclTest
Declare a, Integer
Declare b, Integer
Declare c, Integer
Declare x, Float
Declare y, Float
Declare z, Float_array,10
HALT DeclTest
```

### 2.2. Expressions and Assignments

Arithmetic expressions involving integers and floats are supported, including operators `+`, `-` (unary and binary), `*`, `/`, and parentheses for precedence. Type conversion between integers and floats is handled implicitly in mixed-type expressions and assignments. For example: `a := 5; b := 10.0; c := a + b;` will prmote `a` to float before performing the addition.

**Test Case (`03_expressions.microex` - excerpt):**

```microex
Program ExprTest
Begin
  declare a, b, c, result as integer;
  a := 5; b := 10; c := 2;
  result := a + b * c - (a + b) / c;
end
```

**Generated Assembly:**

```assembly
START ExprTest
Declare a, Integer
Declare b, Integer
Declare c, Integer
Declare result, Integer
I_Store 5,a
I_Store 10,b
I_Store 2,c
I_MUL b,c,T&1
I_ADD a,T&1,T&2
I_ADD a,b,T&3
I_DIV T&3,c,T&4
I_SUB T&2,T&4,T&5
I_Store T&5,result
HALT ExprTest
Declare T&1, Integer
Declare T&2, Integer
Declare T&3, Integer
Declare T&4, Integer
Declare T&5, Integer
```

**Type Conversion Example (`04_typeconversion.microex` - excerpt):**

```microex
  declare i, j as integer;
  declare r as real;
  i := 10; r := 3.14;
  j := i + r;  %% Implicit conversion
```

**Generated Assembly (excerpt):**

```assembly
I_TO_F i,T&2
F_ADD T&2,r,T&1
F_TO_I T&1,T&3
I_Store T&3,j
```

### 2.3. Control Flow Statements

#### 2.3.1. Conditional Statements (IF-THEN-ELSE)

`IF-THEN` and `IF-THEN-ELSE` constructs are implemented, supporting conditions with relational operators (`>`, `<`, `>=`, `<=`, `==`, `!=`).

**Test Case (`05_ifstatement.microex` - excerpt):**

```microex
Program IfTest
Begin
  declare a, b, max as integer;
  a := 10; b := 20;
  if (a > b) then
    max := a;
  else
    max := b;
  endif
end
```

**Generated Assembly:**

```assembly
START IfTest
Declare a, Integer
Declare b, Integer
Declare max, Integer
I_Store 10,a
I_Store 20,b
I_CMP a,b
JLE label_1
I_Store a,max
J label_2
label_1:
I_Store b,max
label_2:
HALT IfTest
```

#### 2.3.2. FOR Loops

FOR loops with TO and DOWNTO clauses are supported for integer loop variables. An optional STEP clause allows specifying a custom integer step value; otherwise, the step defaults to 1 (for TO) or -1 (for DOWNTO).

**Test Case (`06_forloop.microex` - Default Step TO example):**

```microex
Program ForDirectionTest
Begin
  declare i, sum1 as integer;
  sum1 := 0;
  for (i := 1 to 5)
    sum1 := sum1 + i;
  endfor
end
```

**Generated Assembly (excerpt for Default Step TO loop):**

```assembly
START ForDirectionTest
Declare i, Integer
Declare sum1, Integer
I_Store 0,sum1
I_Store 1,i
label_1:
I_CMP i,5
JG label_2
I_ADD sum1,i,T&1
I_Store T&1,sum1
INC i
I_CMP i,5
JLE label_1
label_2:
HALT ForDirectionTest
Declare T&1, Integer
```

**Test Case (13_forstep.microex - Custom STEP example):**

```microex
%% Test FOR loop with STEP
Program ForStepTest
Begin
  declare i, sum, sval as integer;
  sum := 0;
  sval := 2;
  %% Test TO with STEP using a variable
  for (i := 1 to 10 step sval) %% Expected: 1, 3, 5, 7, 9.
    sum := sum + i;
  endfor

  sum := 0;
  %% Test DOWNTO with STEP using a literal
  for (i := 10 downto 1 step 3) %% Expected: 10, 7, 4, 1.
    sum := sum + i;
  endfor
end
```

**Generated Assembly (excerpt for STEP):**

```assembly
START ForStepTest
Declare i, Integer
Declare sum, Integer
Declare sval, Integer
I_Store 0,sum
I_Store 2,sval
I_Store 1,i       // i := 1
label_1:
I_CMP i,10        // Compare i with 10
JG label_2        // Exit if i > 10
I_ADD sum,i,T&1
I_Store T&1,sum
I_ADD i,sval,i    // i := i + sval (step value)
I_CMP i,10
JLE label_1       // Continue if i <= 10
label_2:
// ... (code for second loop) ...
I_Store 0,sum
I_Store 10,i      // i := 10
label_3:
I_CMP i,1         // Compare i with 1
JL label_4        // Exit if i < 1
I_ADD sum,i,T&2
I_Store T&2,sum
I_SUB i,3,i       // i := i - 3 (step value)
I_CMP i,1
JGE label_3       // Continue if i >= 1
label_4:
HALT ForStepTest
Declare T&1, Integer
Declare T&2, Integer
```

#### 2.3.3. WHILE Loops

`WHILE` loops with conditional termination are implemented.

**Test Case (`11_while_declared.microex`):**

```microex
Program WhileTest
begin
  declare i, sum as integer;
  i := 0;
  sum := 0;
  while (i < 5)
    sum := sum + i;
    i := i + 1;
  endwhile
end
```

**Generated Assembly:**

```assembly
START WhileTest
Declare i, Integer
Declare sum, Integer
I_Store 0,i
I_Store 0,sum
label_1:
I_CMP i,5
JGE label_2
I_ADD sum,i,T&1
I_Store T&1,sum
I_ADD i,1,T&2
I_Store T&2,i
J label_1
label_2:
HALT WhileTest
Declare T&1, Integer
Declare T&2, Integer
```

### 2.4. Array Handling

Arrays can be declared with a specified size. Array elements can be accessed using `array_name[index_expression]` syntax in assignments and expressions. The index must be an integer expression.

**Test Case (`07_arrays.microex` - excerpt):**

```microex
Program ArrayTest
Begin
  declare i as integer;
  declare arr[10] as integer;
  i := 5;
  arr[0] := 100;
  arr[i] := arr[0] * 2;
end
```

**Generated Assembly:**

```assembly
START ArrayTest
Declare i, Integer
Declare arr, Integer_array,10
I_Store 5,i
I_Store 100,arr[0]
I_MUL arr[0],2,T&1
I_Store T&1,arr[i]
HALT ArrayTest
Declare T&1, Integer
```

### 2.5. Print Statement

The `PRINT` (and `WRITE`) statement is supported for outputting the values of expressions. Multiple arguments are handled by sequential calls.

> Note that PRINT and WRITE are specified as part of the programming language Micro in Chapter 2 slide.

**Test Case (`12_print.microex`):**

```microex
Program testPrint
Begin
    print(2, 1, 4);
End
```

**Generated Assembly:**

```assembly
START testPrint
CALL print, 2
CALL print, 1
CALL print, 4
HALT testPrint
```

### 2.6. Nested Structures

The compiler supports nesting of control flow structures, such as loops within loops, or conditional statements within loops.

**Test Case (`08_nested.microex` - excerpt):**

```microex
Program NestedTest
Begin
  declare i, j, sum as integer;
  sum := 0;
  for (i := 1 to 5)
    for (j := 1 to i)
      sum := sum + j;
    endfor
    if (sum > 10) then
      sum := sum - 5;
    endif
  endfor
end
```

_(Assembly for nested structures can be lengthy; the successful execution of `08_nested.microex` and `09_combined.microex` demonstrates this capability. The generated Assembly follows the patterns shown in individual control flow sections. To see the result: pleae check the attached output.txt)_

### 2.7. Static Type Checking and Error Handling

The compiler incorporates several static checks to ensure program correctness before attempting to generate code.

**Variable Declaration Enforcement**: As mentioned in section 2.1, all variables must be declared before they are referenced. Attempting to use an undeclared variable results in an error message indicating the variable name and line number, and compilation is halted.

**Example Error for Undeclared Variable:**

```
Error: Variable 'undeclared_var' not declared. at line X
```

**Array Index Type Checking**: Array indices must evaluate to an integer type. Using a float or other non-integer type as an array index will produce an error.

**Example Error for Non-Integer Array Index:**

```
Error: Array index must be an integer. at line Y
```

**FOR Loop Parameter Type Checking:**
The loop control variable in a FOR loop must be of integer type.
The start, end, and optional STEP expressions must also evaluate to integer types.
The compiler will report an error if these conditions are not met.

**Example Error for Non-Integer FOR Loop Parameter:**

```
Error: Loop variable must be an integer. at line Z
Error: FOR loop start expression must be integer. at line Z
Error: FOR loop STEP expression must be integer. at line Z
```

**Type Mismatches in Expressions**: While the compiler performs implicit type promotion from integer to float in mixed-mode arithmetic (e.g., int + float), other more restrictive type checks are in place. For instance, assigning a float expression to an integer variable involves an explicit F_TO_I conversion in the TAC, demonstrating awareness of type differences.

## 3. Techinal Details

This section explains how I built the compiler and how the different parts work together to turn source code into assembly. It also includes comments and my reflections on the process.

## 3.1. How the Compiler Works Overall

My compiler works in three main steps. First, the lexer reads the source code and breaks it into tokens like keywords, numbers, and variable names. Then the parser checks if these tokens follow the grammar rules and builds a symbol table to keep track of variables. At the same time, the parser generates three-address code instructions.

## 3.2. The Lexer

The lexer uses regular expressions to recognize different parts of the code. Here's how I handle different types of tokens:

```c
// Numbers get converted and stored
[0-9]+     { yylval.ival = atoi(yytext); return INT_LITERAL; }
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return FLOAT_LITERAL; }

// Identifiers get added to symbol table immediately
[A-Za-z][A-Za-z0-9]* { yylval.symp = symlook(yytext); return ID; }
```

When the lexer finds something like a number or variable name, it doesn't just pass the text to the parser - it also passes extra information through something called `yylval`. For example, when it sees the number "42", it converts it to an integer and stores it in `yylval.ival`. When it sees a variable name like "x", it calls a function called `symlook()` to add it to the symbol table and passes a pointer to that table entry.

I made an interesting design choice here. Every time the lexer sees a variable name, it immediately adds it to the symbol table, even if we don't know yet whether it's been declared. This makes the parser simpler to write, but it means I have to be careful about checking declaration status later.

### 3.3. Symbol Table (To Keep Track of Everything)

The symbol table is basically a big array that stores information about every variable, array, and temporary value in the program:

```c
struct symtab {
    char *name;        // Variable name like "x" or "T&1"
    int type;          // TYPE_INT(0) or TYPE_FLOAT(1)
    int isArray;       // 0 for regular variables, 1 for arrays
    int size;          // Array size if it's an array
    int is_declared;   // 0 if not declared yet, 1 if declared
};
```

When you give the function `symlook()` a name, it first searches through all existing entries to see if that name already exists:

```c
struct symtab *symlook(char *s) {
    // First, search for existing entry
    for(int i = 0; i < symtab_count; i++) {
        if(strcmp(symtab[i].name, s) == 0) {
            return &symtab[i];  // Found it!
        }
    }

    // Not found, create new entry
    symtab[symtab_count].name = strdup(s);
    symtab[symtab_count].is_declared = 0;     // Mark as not declared
    return &symtab[symtab_count++];
}
```

If it finds the name, it returns a pointer to that entry. If not, it creates a new entry and marks it as not declared yet. This approach lets me handle cases where a variable is used before it's declared (I can catch that error later during parsing).

## 3.4. How Expressions Are Evaluated

One of the trickier parts was figuring out how to handle expressions like "a + b \* c". I use temporary variables to store intermediate results. Here's how the parser rule for addition works:

```c
expression '+' term {
    // Determine result type (float if either operand is float)
    $$.type = ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) ? TYPE_FLOAT : TYPE_INT;

    char *op1_name = $1.place->name;
    char *op2_name = $3.place->name;

    if ($$.type == TYPE_INT) {
        char *temp_res_name = new_temp(TYPE_INT);
        printf("I_ADD %s,%s,%s\n", op1_name, op2_name, temp_res_name);
    } else {
        // Handle type conversions for mixed arithmetic
        if ($1.type == TYPE_INT) {
            char *conv_temp = new_temp(TYPE_FLOAT);
            printf("I_TO_F %s,%s\n", op1_name, conv_temp);
            op1_name = conv_temp;
        }
        char *temp_res_name = new_temp(TYPE_FLOAT);
        printf("F_ADD %s,%s,%s\n", op1_name, op2_name, temp_res_name);
    }
    $$.place = symlook(temp_res_name);
}
```

So for the expression "a + b \* c", the compiler first generates code to multiply b and c and store the result in a temporary called T&1. Then it adds a to T&1 and stores that in T&2.

The type conversion was also challenging. When I have mixed types like adding an integer to a float, I decided to promote the integer to float automatically (just like many modern programming languages). The compiler generates extra instructions to do the conversion, like I_TO_F to convert integer to float.

My `new_temp()` function creates these temporary variables:

```c
char *new_temp(int type) {
    char name_buf[20];
    sprintf(name_buf, "T&%d", ++temp_counter);  // T&1, T&2, T&3...
    struct symtab *s = symlook(name_buf);
    s->type = type;
    s->is_declared = 1;  // Temporaries are automatically declared
    return s->name;
}
```

### 3.5. Variable Declarations and Handling Multiple Variables

Variable declarations like "declare a, b, c as integer" required a special approach because I need to collect all the variable names first, then apply the type to all of them at once. I use a global structure to keep track of the current declaration:

```c
struct {
    struct symtab *ids[100];  // Pointers to symbol table entries
    int count;                // How many variables in this declaration
    int type;                 // What type they'll be
} current_decl;
```

The parsing happens in two steps:

```c
// Step 1: collect variable names
id_decl: ID {
    current_decl.ids[current_decl.count++] = $1;  // Store pointer
}

// Step 2: apply type to all collected variables
declaration_stmt: DECLARE_TOKEN id_list AS_TOKEN type ';' {
    for(int i = 0; i < current_decl.count; i++) {
        current_decl.ids[i]->type = $4;          // Set the type
        current_decl.ids[i]->is_declared = 1;    // Mark as declared
        printf("Declare %s, %s\n", current_decl.ids[i]->name,
               $4 == TYPE_INT ? "Integer" : "Float");
    }
    current_decl.count = 0;  // Reset for next declaration
}
```

### 3.6. Control Flow (Jumps and Labels)

Getting if statements and loops to work required learning about labels and jump instructions. I use a stack-based approach to handle nested structures:

```c
struct label_stack {
    int begin_label;    // Where to jump for else/loop start
    int end_label;      // Where to jump to exit
    char *var_name;     // For FOR loops: loop variable
    char *end_expr;     // For FOR loops: end condition
    char *step_expr;    // For FOR loops: step value
    int is_downto;      // For FOR loops: direction
};

struct label_stack if_stack[20];
int if_stack_ptr = 0;
```

For an if statement, I generate a comparison instruction followed by a conditional jump:

```c
// Condition like "x > 5"
condition: expression '>' expression {
    printf("I_CMP %s,%s\n", $1.place->name, $3.place->name);
    // Jump to else/endif if condition is false (less than or equal)
    printf("JLE label_%d\n", if_stack[if_stack_ptr-1].begin_label);
}
```

The generated code looks like:

```assembly
I_CMP x,5
JLE label_1    // Jump to ELSE if x <= 5
// ... THEN statements ...
J label_2      // Jump over ELSE
label_1:       // ELSE entry point
// ... ELSE statements ...
label_2:       // ENDIF
```

### 3.7. FOR Loops

For loops were the most complicated part of the whole project. A simple for loop like "for i := 1 to 10" needs several pieces: initialization, condition checking, loop body, increment, and jump back. Adding the STEP feature and DOWNTO direction made it even more complex.

Here's how I handle the setup:

```c
for_header: FOR_TOKEN '(' ID ASSIGN_OP expression TO_TOKEN expression optional_step ')' {
    // Initialize loop variable: i := 1
    printf("I_Store %s,%s\n", $5.place->name, $3->name);

    // Set up loop tracking
    for_stack[for_stack_ptr].var_name = strdup($3->name);      // "i"
    for_stack[for_stack_ptr].end_expr = strdup($7.place->name); // "10"
    for_stack[for_stack_ptr].begin_label = new_label();
    for_stack[for_stack_ptr].end_label = new_label();

    // Handle optional step
    if ($8.place != NULL) {
        for_stack[for_stack_ptr].step_expr = strdup($8.place->name);
    } else {
        for_stack[for_stack_ptr].step_expr = NULL; // Default step
    }

    // Generate loop entry
    printf("label_%d:\n", for_stack[for_stack_ptr].begin_label);
    printf("I_CMP %s,%s\n", $3->name, $7.place->name);  // Compare i with 10
    printf("JG label_%d\n", for_stack[for_stack_ptr].end_label);  // Exit if i > 10
}
```

The STEP feature was tricky because I needed to handle four different cases. At the end of the loop, I check whether there's a custom step value and whether it's counting up (TO) or down (DOWNTO):

```c
for_stmt: for_header stmt_list ENDFOR_TOKEN {
    char* step_val_str = for_stack[for_stack_ptr-1].step_expr;

    if (step_val_str == NULL) {
        // Default step: increment or decrement by 1
        if (for_stack[for_stack_ptr-1].is_downto) {
            printf("DEC %s\n", for_stack[for_stack_ptr-1].var_name);
        } else {
            printf("INC %s\n", for_stack[for_stack_ptr-1].var_name);
        }
    } else {
        // Custom step: add or subtract the step value
        if (for_stack[for_stack_ptr-1].is_downto) {
            printf("I_SUB %s,%s,%s\n", var_name, step_val_str, var_name);
        } else {
            printf("I_ADD %s,%s,%s\n", var_name, step_val_str, var_name);
        }
    }

    // Check condition and jump back if needed
    printf("I_CMP %s,%s\n", var_name, end_expr);
    if (is_downto) {
        printf("JGE label_%d\n", begin_label); // Continue if i >= end
    } else {
        printf("JLE label_%d\n", begin_label); // Continue if i <= end
    }
    printf("label_%d:\n", end_label);
}
```

So for "for (i := 1 to 10 step 3)", it generates code that adds 3 to i each time instead of just incrementing by 1. For "for (i := 10 downto 1 step 2)", it subtracts 2 from i each iteration. The jump conditions are also different. TO loops continue while i <= end, but DOWNTO loops continue while i >= end.

The challenging part was keeping track of all the different combinations and making sure the memory management worked correctly since I use `strdup()` to store the variable names and step expressions.

### 3.8. WHILE Loops

WHILE loops are simpler than FOR loops but still required careful label management. The basic idea is to check the condition at the beginning of each iteration and jump out if it's false.

Here's how I set up a WHILE loop:

```c
while_header: WHILE_TOKEN '(' {
    // Set up labels for this while loop
    if_stack[if_stack_ptr].begin_label = new_label();  // Loop start
    if_stack[if_stack_ptr].end_label = new_label();    // Loop exit
    if_stack_ptr++;
    printf("label_%d:\n", if_stack[if_stack_ptr-1].begin_label);
    in_while_loop = 1;  // Flag to help with condition handling
} condition ')' {
    in_while_loop = 0;
}
```

I reuse the same if_stack that I use for IF statements since WHILE loops need the same kind of label management. The condition parsing generates a jump to the end label if the condition is false.

At the end of the loop, I generate a jump back to the beginning:

```c
while_stmt: while_header stmt_list ENDWHILE_TOKEN {
    printf("J label_%d\n", if_stack[if_stack_ptr-1].begin_label);  // Jump back to start
    printf("label_%d:\n", if_stack[if_stack_ptr-1].end_label);     // Exit label
    if_stack_ptr--;
}
```

For a loop like "while (i < 5)", the generated code looks like:

```assembly
label_1:          // Loop start
I_CMP i,5         // Compare i with 5
JGE label_2       // Exit if i >= 5
// ... loop body ...
J label_1         // Jump back to start
label_2:          // Exit point
```

The `in_while_loop` flag helps the condition parsing know whether to jump to an exit label (for WHILE) or an else label (for IF statements). It's a simple but effective way to reuse the same condition handling code.

### 3.9. Arrays

Arrays required a different approach because the assignment "arr[i] := 5" involves two grammar rules. The left side "arr[i]" is parsed as an lvalue, while the assignment as a whole is parsed separately. I solved this by using a global variable to pass information between these rules:

```c
struct {
    struct symtab *array;
    struct symtab *index;
} current_array_access;
```

When parsing the left side of an assignment:

```c
lvalue: ID '[' expression ']' {
    // Store array and index information globally
    current_array_access.array = $1;      // The array
    current_array_access.index = $3.place; // The index expression result
    $$ = $1;
}
```

Then in the assignment rule, I check if we're dealing with an array:

```c
assignment_stmt: lvalue ASSIGN_OP expression ';' {
    if (current_array_access.array != NULL) {
        // Array assignment
        char target_operand_name[100];
        sprintf(target_operand_name, "%s[%s]",
                current_array_access.array->name,
                current_array_access.index->name);
        printf("I_Store %s,%s\n", $3.place->name, target_operand_name);
        current_array_access.array = NULL;  // Reset
    } else {
        // Regular variable assignment
        printf("I_Store %s,%s\n", $3.place->name, $1->name);
    }
}
```

### 3.10. Type System and Conversions

I wanted the language to be user-friendly, so I implemented automatic type conversion (just like modern programming languages). The challenge was making sure I covered all the combinations. Here's how assignment conversion works:

```c
assignment_stmt: lvalue ASSIGN_OP expression ';' {
    if ($1->type == TYPE_INT) {
        if ($3.type == TYPE_INT) {
            // int := int
            printf("I_Store %s,%s\n", $3.place->name, $1->name);
        } else {
            // int := float (need conversion)
            char *temp = new_temp(TYPE_INT);
            printf("F_TO_I %s,%s\n", $3.place->name, temp);
            printf("I_Store %s,%s\n", temp, $1->name);
        }
    } else { // $1->type == TYPE_FLOAT
        if ($3.type == TYPE_INT) {
            // float := int (need conversion)
            char *temp = new_temp(TYPE_FLOAT);
            printf("I_TO_F %s,%s\n", $3.place->name, temp);
            printf("F_Store %s,%s\n", temp, $1->name);
        } else {
            // float := float
            printf("F_Store %s,%s\n", $3.place->name, $1->name);
        }
    }
}
```

There are four cases for assignments: int to int, int to float, float to int, and float to float. Each one needs different instruction sequences, and I had to make sure array assignments worked the same way as regular variable assignments.

### 3.11. Error Checking and Validation

I tried to make error messages helpful rather than just saying "syntax error" (default behavior). The error checking happens at different stages:

```c
// Check for undeclared variables during expression parsing
factor: ID {
    if (!$1->is_declared) {
        char err_msg[100];
        sprintf(err_msg, "Variable '%s' not declared.", $1->name);
        yyerror(err_msg);
    }
    $$.place = $1;
    $$.type = $1->type;
}

// Check array index types
lvalue: ID '[' expression ']' {
    if ($3.type != TYPE_INT) {
        yyerror("Array index must be an integer.");
    }
    // ... rest of array handling
}
```

Some errors like undeclared variables are caught during parsing when I try to use a symbol table entry that's marked as not declared. Other errors like type mismatches in for loop parameters are caught when setting up the loop structure.

### 3.12. Code Generation Strategy

The final output is three-address code, which means each instruction has at most three operands. I use different prefixes for different types of operations:

- `I_` for integer operations: `I_ADD`, `I_SUB`, `I_MUL`, `I_DIV`
- `F_` for float operations: `F_ADD`, `F_SUB`, `F_MUL`, `F_DIV`
- Conversion operations: `I_TO_F`, `F_TO_I`
- Memory operations: `I_Store`, `F_Store`
- Control flow: `I_CMP`, `F_CMP`, `JLE`, `JG`, `J`

## 4. Conclusion and Future Work

My Micro/Ex compiler successfully implements core programming language features including declarations, arithmetic expressions with type conversion, assignments, array handling, and fundamental control flow statements (IF, FOR with STEP, WHILE). Static type checks for variable usage, array indexing, and loop parameters for robustness.

Future work could include:

- Support for sophisticated logical expressions using `AND`, `OR`, `NOT`.
- Addition of user-defined functions with parameter passing and return values.

## Appendix

Included files:

- Source code in `src` directory
- Test cases in `test` directory
- Assembly output for all test cases in `output.txt`
