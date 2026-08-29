%{
#include <stdio.h>
%}

%%
https?://.*    { printf("Valid URL\n"); }
.*             { printf("Invalid URL\n"); }
%%

int main()
{
    printf("Enter URL: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
