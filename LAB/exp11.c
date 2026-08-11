%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

struct symtab {
    char label[20];
    int addr;
} sy[MAX];

int cnt = 0;
int flag = 0;

int search(char *s) {
    int i;
    for(i = 0; i < cnt; i++) {
        if(strcmp(sy[i].label, s) == 0)
            return 1;
    }
    return 0;
}

void insert(char *lab, int addr) {
    if(search(lab)) {
        printf("Duplicate symbol: %s\n", lab);
    } else {
        strcpy(sy[cnt].label, lab);
        sy[cnt].addr = addr;
        cnt++;
        printf("Inserted: %s at address %d\n", lab, addr);
    }
}

void display() {
    int i;
    printf("\n--- Symbol Table ---\n");
    printf("Label\t\tAddress\n");
    printf("------------------\n");
    for(i = 0; i < cnt; i++) {
        printf("%s\t\t%d\n", sy[i].label, sy[i].addr);
    }
}

void modify(char *lab, int addr) {
    int i;
    if(!search(lab)) {
        printf("Symbol %s not found\n", lab);
    } else {
        for(i = 0; i < cnt; i++) {
            if(strcmp(sy[i].label, lab) == 0) {
                sy[i].addr = addr;
                printf("Updated: %s to address %d\n", lab, addr);
                break;
            }
        }
    }
}

void delete(char *lab) {
    int i, j;
    if(!search(lab)) {
        printf("Symbol %s not found\n", lab);
    } else {
        for(i = 0; i < cnt; i++) {
            if(strcmp(sy[i].label, lab) == 0) {
                for(j = i; j < cnt - 1; j++) {
                    strcpy(sy[j].label, sy[j+1].label);
                    sy[j].addr = sy[j+1].addr;
                }
                cnt--;
                printf("Deleted: %s\n", lab);
                break;
            }
        }
    }
}
%}

%%

"insert"[ \t]+[a-zA-Z]+[ \t]+[0-9]+  {
    char lab[20];
    int addr;
    sscanf(yytext, "insert %s %d", lab, &addr);
    insert(lab, addr);
}

"display"         { display(); }

"modify"[ \t]+[a-zA-Z]+[ \t]+[0-9]+  {
    char lab[20];
    int addr;
    sscanf(yytext, "modify %s %d", lab, &addr);
    modify(lab, addr);
}

"delete"[ \t]+[a-zA-Z]+  {
    char lab[20];
    sscanf(yytext, "delete %s", lab);
    delete(lab);
}

"search"[ \t]+[a-zA-Z]+  {
    char lab[20];
    sscanf(yytext, "search %s", lab);
    if(search(lab)) {
        printf("Symbol %s found\n", lab);
    } else {
        printf("Symbol %s not found\n", lab);
    }
}

"exit"            { printf("Exiting...\n"); exit(0); }

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Symbol Table Operations\n");
    printf("Commands:\n");
    printf("  insert <label> <address>\n");
    printf("  display\n");
    printf("  modify <label> <address>\n");
    printf("  delete <label>\n");
    printf("  search <label>\n");
    printf("  exit\n");
    printf("----------------------------\n");
    printf("Enter command: ");
    yylex();
    return 0;
}