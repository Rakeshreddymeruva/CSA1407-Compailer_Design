%{
#include <stdio.h>
#include <string.h>

int keyword_count = 0, id_count = 0, const_count = 0, op_count = 0;

char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "unsigned", "void", "while",
    "printf", "main"
};

int isKeyword(char *str) {
    int i;
    for(i = 0; i < 32; i++) {
        if(strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%%

[ \t\n]+          { /* Ignore spaces, tabs, newlines */ }

"//"[^\n]*        { /* Ignore single-line comments */ }

"/*"[^*]*"*/"     { /* Ignore multi-line comments */ }

[a-zA-Z_][a-zA-Z0-9_]*  {
    if(isKeyword(yytext)) {
        printf("Keyword: %s\n", yytext);
        keyword_count++;
    } else {
        printf("Identifier: %s\n", yytext);
        id_count++;
    }
}

[0-9]+            { printf("Constant: %s\n", yytext); const_count++; }

"+"               { printf("Operator: +\n"); op_count++; }
"-"               { printf("Operator: -\n"); op_count++; }
"*"               { printf("Operator: *\n"); op_count++; }
"/"               { printf("Operator: /\n"); op_count++; }
"="               { printf("Operator: =\n"); op_count++; }
"%"               { printf("Operator: %%\n"); op_count++; }
"<"               { printf("Operator: <\n"); op_count++; }
">"               { printf("Operator: >\n"); op_count++; }
"!"               { printf("Operator: !\n"); op_count++; }
"=="              { printf("Operator: ==\n"); op_count++; }
"!="              { printf("Operator: !=\n"); op_count++; }
"<="              { printf("Operator: <=\n"); op_count++; }
">="              { printf("Operator: >=\n"); op_count++; }

.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: exp3.exe input.c\n");
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    
    yylex();
    
    printf("\n--- Summary ---\n");
    printf("Keywords: %d\n", keyword_count);
    printf("Identifiers: %d\n", id_count);
    printf("Constants: %d\n", const_count);
    printf("Operators: %d\n", op_count);
    
    fclose(yyin);
    return 0;
}