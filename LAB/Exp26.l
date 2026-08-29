%{
#include<stdio.h>
%}

%%
[a-zA-Z0-9._]+@[a-zA-Z0-9.]+\.[a-zA-Z]{2,3}    { printf("Valid Email\n"); }
.*                                             { printf("Invalid Email\n"); }
%%

int main()
{
    printf("Enter Email: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
