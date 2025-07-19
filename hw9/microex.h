#ifndef MICROEX_H
#define MICROEX_H

#define NSYMS 100 /* maximum number of symbols */

struct symtab {
    char *name;
    int type;      // 0=INTEGER, 1=REAL
    int isArray;   // 0=scalar, 1=array
    int size;      // array size if isArray=1
};

extern struct symtab symtab[NSYMS];
extern int symtab_count;

struct symtab *symlook(char *s);

#endif
