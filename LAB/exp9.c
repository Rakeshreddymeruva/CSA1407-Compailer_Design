%{
#include <stdio.h>
#include <string.h>

char non_terminal;
char alpha, beta;
int has_left_recursion = 0;
%}

%%

^[A-Z]"->"[A-Z][A-Za-z]+  {
    non_terminal = yytext[0];
    char ch = yytext[2];
    
    if(non_terminal == ch) {
        printf("Grammar: %s is left recursive.\n", yytext);
        has_left_recursion = 1;
        
        // Extract alpha and beta
        alpha = yytext[3];
        
        // Find beta (rest of production)
        char beta_part[20];
        int i, j = 0;
        for(i = 3; yytext[i] != '\0'; i++) {
            if(yytext[i] == '|') {
                i++;
                while(yytext[i] != '\0') {
                    beta_part[j++] = yytext[i];
                    i++;
                }
                beta_part[j] = '\0';
                break;
            }
        }
        
        if(strlen(beta_part) > 0) {
            printf("Grammar without left recursion:\n");
            printf("%c->%s%c'\n", non_terminal, beta_part, non_terminal);
            printf("%c'->%c%c'|$\n", non_terminal, alpha, non_terminal);
        }
    } else {
        printf("Grammar: %s is not left recursive.\n", yytext);
    }
}

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter grammar (e.g., S->AaAb|BbBa):\n");
    yylex();
    return 0;
}