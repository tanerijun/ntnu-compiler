#include "calc.h"

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    return yyparse();
}
