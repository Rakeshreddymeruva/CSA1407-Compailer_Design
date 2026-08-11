%{
#include <stdio.h>
#include <string.h>

int id_count = 0, const_count = 0, op_count = 0;
%}

%%

[ \t\n]+          { /* Ignore spaces, tabs, newlines */ }

[a-zA-Z]+         { printf("Identifier: %s\n", yytext); id_count++; }

[0-9]+            { printf("Constant: %s\n", yytext); const_count++; }

"+"               { printf("Operator: +\n"); op_count++; }
"-"               { printf("Operator: -\n"); op_count++; }
"*"               { printf("Operator: *\n"); op_count++; }
"/"               { printf("Operator: /\n"); op_count++; }
"="               { printf("Operator: =\n"); op_count++; }
"%"               { printf("Operator: %%\n"); op_count++; }

.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a string: ");
    yylex();
    
    printf("\n--- Summary ---\n");
    printf("Total Identifiers: %d\n", id_count);
    printf("Total Constants: %d\n", const_count);
    printf("Total Operators: %d\n", op_count);
    
    return 0;
}