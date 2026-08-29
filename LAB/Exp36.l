%{
#include <stdio.h>
%}

%%
[0-9]+      { printf("Number: %s\n", yytext); }
"+"         { printf("Addition operator\n"); }
"-"         { printf("Subtraction operator\n"); }
"*"         { printf("Multiplication operator\n"); }
"/"         { printf("Division operator\n"); }
[ \t\n]+    ;
.           { printf("Invalid symbol: %s\n", yytext); }
%%

int main()
{
    printf("Enter an arithmetic expression: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}