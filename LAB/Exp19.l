%{
#include <stdio.h>

int characters = 0;
int words = 0;
int lines = 0;
%}

%%
\n          { characters++; lines++; }
[ \t]+      { characters += yyleng; }
[^ \t\n]+   { characters += yyleng; words++; }
%%

int main()
{
    yyin = fopen("sample.c", "r");

    if (yyin == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    yylex();

    printf("\nNumber of characters = %d", characters);
    printf("\nNumber of words      = %d", words);
    printf("\nNumber of lines      = %d\n", lines);

    fclose(yyin);
    return 0;
}

int yywrap()
{
    return 1;
}