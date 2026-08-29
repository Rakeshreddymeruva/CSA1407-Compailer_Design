%{
#include <stdio.h>
%}

%%
[0-9]       { printf("%s is a digit\n", yytext); }
[^0-9\n]    { printf("%s is not a digit\n", yytext); }
\n          ;
%%

int main()
{
    printf("Enter a character: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}