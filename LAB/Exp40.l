%{
#include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*    { printf("Identifier: %s\n", yytext); }
[0-9]+                    { printf("Number: %s\n", yytext); }
[+\-*/=]                  { printf("Operator: %s\n", yytext); }
[(){};,]                  { printf("Separator: %s\n", yytext); }
[ \t\n]+                  ;
.                         { printf("Invalid symbol: %s\n", yytext); }
%%

int main()
{
    printf("Enter an expression:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
