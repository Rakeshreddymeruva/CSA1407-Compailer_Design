%{
#include <stdio.h>

int comments = 0;
%}

%%
"//".*                  { comments++; }
"/*"([^*]|\*+[^*/])*\*+"/"   { comments++; }
\n                      { fputc('\n', yyout); }
.                       { fputc(yytext[0], yyout); }
%%

int main()
{
    yyin = fopen("input.c", "r");
    yyout = fopen("output.c", "w");

    if (yyin == NULL)
    {
        printf("Input file not found!\n");
        return 1;
    }

    yylex();

    printf("Number of comments = %d\n", comments);
    printf("Comments removed successfully.\n");

    fclose(yyin);
    fclose(yyout);

    return 0;
}

int yywrap()
{
    return 1;
}