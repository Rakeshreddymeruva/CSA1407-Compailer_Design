%{
#include <stdio.h>
%}

%%
abc     { printf("ABC"); }
\n      { printf("\n"); }
.       { printf("%s", yytext); }
%%

int main()
{
    printf("Enter a string:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}