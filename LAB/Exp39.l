%{
#include <stdio.h>
#include <string.h>

char oldword[50];
char newword[50];
%}

%%
[a-zA-Z]+    {
    if (strcmp(yytext, oldword) == 0)
        fprintf(yyout, "%s", newword);
    else
        fprintf(yyout, "%s", yytext);
}

.|\n          {
    fprintf(yyout, "%s", yytext);
}
%%

int main()
{
    printf("Enter word to replace: ");
    scanf("%49s", oldword);

    printf("Enter new word: ");
    scanf("%49s", newword);

    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");

    if (yyin == NULL)
    {
        printf("Input file not found!\n");
        return 1;
    }

    if (yyout == NULL)
    {
        printf("Could not create output file!\n");
        fclose(yyin);
        return 1;
    }

    yylex();

    fclose(yyin);
    fclose(yyout);

    printf("Replacement completed.\n");

    return 0;
}

int yywrap()
{
    return 1;
}
