%{
#include<stdio.h>
%}

%%
[0-9/]+    { printf("Valid DOB\n"); }
.|\n       { printf("Invalid DOB\n"); }
%%

int main()
{
    printf("Enter DOB: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
