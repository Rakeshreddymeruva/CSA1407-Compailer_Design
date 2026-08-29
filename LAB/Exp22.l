%{
#include <stdio.h>
%}

%%
\<[^>]*>    { printf("HTML Tag: %s\n", yytext); }
.|\n        ;
%%

int main()
{
    yyin = fopen("sample.html", "r");

    if (yyin == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    yylex();
    fclose(yyin);

    return 0;
}

int yywrap()
{
    return 1;
}