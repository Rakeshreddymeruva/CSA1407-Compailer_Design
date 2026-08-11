%{
#include <stdio.h>
int single_line = 0, multi_line = 0;
%}

%%

"//"[^\n]*        { printf("Single-line comment: %s\n", yytext); single_line++; }

"/*"[^*]*"*/"     { printf("Multi-line comment: %s\n", yytext); multi_line++; }

[ \t\n]+          { /* Ignore whitespace */ }

.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string with comments: ");
    yylex();
    
    printf("\n--- Summary ---\n");
    printf("Single-line comments: %d\n", single_line);
    printf("Multi-line comments: %d\n", multi_line);
    
    return 0;
}