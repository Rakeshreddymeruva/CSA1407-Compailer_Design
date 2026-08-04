%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char productions[MAX][MAX];
int num_productions = 0;

void add_production(char *prod) {
    strcpy(productions[num_productions], prod);
    num_productions++;
}

void find_first(char non_terminal) {
    int i, j;
    int first_set[10];
    int count = 0;
    int found;
    
    printf("FIRST(%c) = { ", non_terminal);
    
    for(i = 0; i < num_productions; i++) {
        if(productions[i][0] == non_terminal) {
            char ch = productions[i][2];
            
            if(!isupper(ch) && ch != '$') {
                // Check if already in set
                found = 0;
                for(j = 0; j < count; j++) {
                    if(first_set[j] == ch) found = 1;
                }
                if(!found) {
                    printf("%c ", ch);
                    first_set[count++] = ch;
                }
            }
        }
    }
    printf("}\n");
}
%}

%%

[a-zA-Z]"->"[a-zA-Z$]+  { 
    add_production(yytext); 
}

[ \t\n]+              { /* Ignore whitespace */ }

.                     { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: exp7.exe grammar.txt\n");
        printf("Grammar format: S->AaAb or A->$\n");
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    
    yylex();
    
    printf("\n--- Grammar Productions ---\n");
    for(int i = 0; i < num_productions; i++) {
        printf("%d: %s\n", i+1, productions[i]);
    }
    
    printf("\n--- FIRST Sets ---\n");
    char non_terminals[MAX];
    int nt_count = 0;
    
    // Collect unique non-terminals
    for(int i = 0; i < num_productions; i++) {
        char nt = productions[i][0];
        int found = 0;
        for(int j = 0; j < nt_count; j++) {
            if(non_terminals[j] == nt) {
                found = 1;
                break;
            }
        }
        if(!found) {
            non_terminals[nt_count] = nt;
            nt_count++;
        }
    }
    
    // Find FIRST for each non-terminal
    for(int i = 0; i < nt_count; i++) {
        find_first(non_terminals[i]);
    }
    
    fclose(yyin);
    return 0;
}