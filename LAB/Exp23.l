%{
#include <stdio.h>

int line = 1;
%}

%%
\n          { printf("\n%3d ", ++line); }
.           { printf("%s", yytext); }
%%

int main()
{
    yyin = fopen("sample.c", "r");

    if (yyin == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    printf("%3d ", line);
    yylex();

    fclose(yyin);
    return 0;
}

int yywrap()
{
    return 1;
}