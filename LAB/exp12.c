%{
#include <stdio.h>
#include <string.h>

char str[100];  // Renamed from 'input' to 'str'
int i, len;

int E();
int EP();
int T();
int TP();
int F();

int E() {
    if(T()) {
        if(EP())
            return 1;
        else
            return 0;
    }
    return 0;
}

int EP() {
    if(str[i] == '+') {
        i++;
        if(T()) {
            if(EP())
                return 1;
            else
                return 0;
        }
        return 0;
    }
    return 1; // epsilon
}

int T() {
    if(F()) {
        if(TP())
            return 1;
        else
            return 0;
    }
    return 0;
}

int TP() {
    if(str[i] == '*') {
        i++;
        if(F()) {
            if(TP())
                return 1;
            else
                return 0;
        }
        return 0;
    }
    return 1; // epsilon
}

int F() {
    if(str[i] == '(') {
        i++;
        if(E()) {
            if(str[i] == ')') {
                i++;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    else if((str[i] >= 'a' && str[i] <= 'z') || 
            (str[i] >= 'A' && str[i] <= 'Z')) {
        i++;
        return 1;
    }
    return 0;
}
%}

%%

.*\n              {
    strcpy(str, yytext);
    str[strcspn(str, "\n")] = '\0';
    i = 0;
    len = strlen(str);
    
    printf("Parsing: %s\n", str);
    
    if(E()) {
        if(str[i] == '\0')
            printf("String is accepted\n");
        else
            printf("String is not accepted (extra characters)\n");
    } else {
        printf("String is not accepted\n");
    }
}

[ \t]+            { /* Ignore whitespace */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Recursive Descent Parsing\n");
    printf("Grammar: E->TE', E'->+TE'|$, T->FT', T'->*FT'|$, F->(E)|id\n");
    printf("Enter strings to parse (Ctrl+C to exit):\n");
    yylex();
    return 0;
}