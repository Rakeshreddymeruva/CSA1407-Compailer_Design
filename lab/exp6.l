%{
#include <stdio.h>
int valid = 0, invalid = 0;
%}

%%

^[a-zA-Z_][a-zA-Z0-9_]*$  { printf("%s is a VALID identifier\n", yytext); valid++; }

[a-zA-Z_][a-zA-Z0-9_]*    { printf("%s is a VALID identifier\n", yytext); valid++; }

[0-9][a-zA-Z0-9_]*        { printf("%s is INVALID identifier (starts with digit)\n", yytext); invalid++; }

[ \t\n]+          { /* Ignore whitespace */ }
.                 { printf("'%s' is INVALID identifier\n", yytext); invalid++; }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter identifiers (one per line, press Ctrl+Z then Enter to end):\n");
    yylex();
    
    printf("\n--- Summary ---\n");
    printf("Valid identifiers: %d\n", valid);
    printf("Invalid identifiers: %d\n", invalid);
    
    return 0;
}