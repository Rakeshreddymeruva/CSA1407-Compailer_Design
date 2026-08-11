%{
#include <stdio.h>
#include <string.h>

char gram[100], part1[100], part2[100], modifiedGram[100], newGram[100];
%}

%%

^[A-Z]"->"[A-Za-z|]+  {
    strcpy(gram, yytext);
    printf("Original: %s\n", gram);
    
    int i, j = 0, k = 0, pos;
    
    // Extract first production
    for(i = 2; gram[i] != '|' && gram[i] != '\0'; i++, j++) {
        part1[j] = gram[i];
    }
    part1[j] = '\0';
    
    // Extract second production
    i++; // skip '|'
    for(j = 0; gram[i] != '\0' && gram[i] != '|'; i++, j++) {
        part2[j] = gram[i];
    }
    part2[j] = '\0';
    
    // Find common prefix
    for(i = 0; i < strlen(part1) && i < strlen(part2); i++) {
        if(part1[i] == part2[i]) {
            modifiedGram[k] = part1[i];
            k++;
            pos = i + 1;
        } else {
            break;
        }
    }
    
    // Create new productions
    int n = 0;
    for(i = pos; part1[i] != '\0'; i++, n++) {
        newGram[n] = part1[i];
    }
    newGram[n++] = '|';
    for(i = pos; part2[i] != '\0'; i++, n++) {
        newGram[n] = part2[i];
    }
    newGram[n] = '\0';
    
    modifiedGram[k] = 'X';
    modifiedGram[++k] = '\0';
    
    printf("After left factoring:\n");
    printf("%c->%s\n", gram[0], modifiedGram);
    printf("X->%s\n", newGram);
}

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter grammar (e.g., S->iEtS|iEtSeS|a):\n");
    yylex();
    return 0;
}