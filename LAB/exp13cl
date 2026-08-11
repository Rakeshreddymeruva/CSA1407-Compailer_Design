%{
#include <stdio.h>
#include <string.h>

char str[100];  // Changed from 'input' to 'str'
int pos = 0;
int len = 0;

int parse(char *s) {
    int i = 0;
    int len_s = strlen(s);
    
    if(s[0] != 'a') {
        return 0;
    }
    
    i = 1;
    int flag = 0;
    while(i < len_s) {
        if(s[i] == 'b') {
            flag = 1;
            i++;
            while(i < len_s && s[i] == 'b') {
                i++;
            }
            if(i == len_s)
                return 1;
            else
                return 0;
        } else if(s[i] == 'a') {
            if(flag == 1) {
                return 0;
            }
            i++;
        } else {
            return 0;
        }
    }
    return 0;
}
%}

%%

[a-z]+            { 
    if(parse(yytext)) {
        printf("%s is ACCEPTED\n", yytext);
    } else {
        printf("%s is NOT ACCEPTED\n", yytext);
    }
}

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Top-Down Parsing\n");
    printf("Grammar: S->aS, S->Sb, S->ab\n");
    printf("\nEnter strings (press Ctrl+Z then Enter to end):\n");
    yylex();
    return 0;
}