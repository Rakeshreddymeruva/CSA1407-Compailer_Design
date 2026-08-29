%{
#include <stdio.h>

int positive = 0;
int negative = 0;
%}

%%
-[0-9]+     { printf("Negative: %s\n", yytext); negative++; }
\+?[0-9]+   { printf("Positive: %s\n", yytext); positive++; }
[ \t\n]+    ;
.           ;
%%

int main()
{
    printf("Enter numbers:\n");
    yylex();

    printf("\nPositive numbers = %d\n", positive);
    printf("Negative numbers = %d\n", negative);

    return 0;
}

int yywrap()
{
    return 1;
}