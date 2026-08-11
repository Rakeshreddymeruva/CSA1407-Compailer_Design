%{
#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
    stack[top+1] = '\0';
}

void pop() {
    if(top >= 0)
        top--;
    stack[top+1] = '\0';
}

int is_terminal(char c) {
    return (c == 'a' || c == 'b');
}

void reduce() {
    if(top >= 2) {
        if(stack[top] == 'a' && stack[top-1] == '+' && stack[top-2] == 'E') {
            top = top - 2;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduced: E->E+a\n");
        } else if(stack[top] == 'b' && stack[top-1] == '+' && stack[top-2] == 'E') {
            top = top - 2;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduced: E->E+b\n");
        } else if(stack[top] == 'a' && stack[top-1] == '*' && stack[top-2] == 'E') {
            top = top - 2;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduced: E->E*a\n");
        } else if(stack[top] == 'b' && stack[top-1] == '*' && stack[top-2] == 'E') {
            top = top - 2;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduced: E->E*b\n");
        }
    }
    if(top == 0 && stack[0] == 'a') {
        stack[0] = 'E';
        printf("Reduced: E->a\n");
    }
    if(top == 0 && stack[0] == 'b') {
        stack[0] = 'E';
        printf("Reduced: E->b\n");
    }
}

void parse(char *str) {
    int len = strlen(str);
    printf("\nShift-Reduce Parsing\n");
    printf("Grammar: E->E+E, E->E*E, E->a, E->b\n");
    printf("\nStack\t\tInput\t\tAction\n");
    printf("--------------------------------\n");
    
    for(int i = 0; i < len; i++) {
        push(str[i]);
        printf("%s\t\t%s\t\tShift\n", stack, str+i+1);
        
        reduce();
        if(top >= 0 && stack[top] != 'E') {
            // No reduction, continue
        }
    }
    
    // Final reduction
    while(top > 0) {
        reduce();
        if(top == 0 && stack[0] == 'E') {
            printf("%s\t\t$\t\tACCEPT\n", stack);
            break;
        }
    }
}
%}

%%

[a+b*]+           { parse(yytext); }

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter expression (use a, b, +, *): ");
    yylex();
    return 0;
}