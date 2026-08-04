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

void find_follow(char non_terminal) {
    int i, j, k;
    int follow_set[10];
    int count = 0;
    int found;
    
    printf("FOLLOW(%c) = { ", non_terminal);
    
    // Add $ to FOLLOW of start symbol
    if(non_terminal == productions[0][0]) {
        printf("$ ");
        follow_set[count++] = '$';
    }
    
    // Search in all productions
    for(i = 0; i < num_productions; i++) {
        int len = strlen(productions[i]);
        for(j = 2; j < len; j++) {
            if(productions[i][j] == non_terminal) {
                // Check if next character exists
                if(j + 1 < len) {
                    char next = productions[i][j + 1];
                    if(!isupper(next)) {
                        // Terminal - add to follow
                        found = 0;
                        for(k = 0; k < count; k++) {
                            if(follow_set[k] == next) found = 1;
                        }
                        if(!found) {
                            printf("%c ", next);
                            follow_set[count++] = next;
                        }
                    }
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
        printf("Usage: exp8.exe grammar.txt\n");
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
    
    printf("\n--- FOLLOW Sets ---\n");
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
    
    // Find FOLLOW for each non-terminal
    for(int i = 0; i < nt_count; i++) {
        find_follow(non_terminals[i]);
    }
    
    fclose(yyin);
    return 0;
}