%{
#include <stdio.h>

int spaces = 0, tabs = 0, newlines = 0, chars = 0;
%}

%%

" "               { spaces++; chars++; }
"\t"              { tabs++; chars++; }
"\n"              { newlines++; chars++; }
.                 { chars++; }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: exp5.exe input.txt\n");
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if(yyin == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    
    yylex();
    
    printf("\n--- Summary ---\n");
    printf("Spaces: %d\n", spaces);
    printf("Tabs: %d\n", tabs);
    printf("Newlines: %d\n", newlines);
    printf("Total Characters: %d\n", chars);
    
    fclose(yyin);
    return 0;
}