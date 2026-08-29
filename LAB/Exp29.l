%{
#include <stdio.h>
%}

%%
"int"|"float"|"char"|"void"|"return"|"if"|"else"|"while"|"for" {
    printf("KEYWORD     : %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER  : %s\n", yytext);
}

[0-9]+ {
    printf("CONSTANT    : %s\n", yytext);
}

"=="|"!="|"<="|">="|"+"|"-"|"*"|"/"|"="|"<"|">" {
    printf("OPERATOR    : %s\n", yytext);
}

[(){};,] {
    printf("SPECIAL     : %s\n", yytext);
}

[ \t\n]+ ;

. {
    printf("UNKNOWN     : %s\n", yytext);
}

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
    fclose(yyin);

    return 0;
}

int yywrap()
{
    return 1;
}