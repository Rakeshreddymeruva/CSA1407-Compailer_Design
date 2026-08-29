%{
#include <stdio.h>
#include <string.h>

char longest[100] = "";
%}

%%
[a-zA-Z]+    {
    if (strlen(yytext) > strlen(longest))
        strcpy(longest, yytext);
}
\n           ;
.            ;
%%

int main()
{
    printf("Enter a sentence:\n");
    yylex();

    printf("Longest word = %s\n", longest);
    printf("Length = %d\n", (int)strlen(longest));

    return 0;
}

int yywrap()
{
    return 1;
}
