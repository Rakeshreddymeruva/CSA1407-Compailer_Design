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

int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        default:
            return -1;
    }
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void evaluate(char *expr) {
    char output[100];
    int out_pos = 0;
    int len = strlen(expr);
    
    printf("\nOperator Precedence Parsing\n");
    printf("Converting to Postfix...\n\n");
    
    for(int i = 0; i < len; i++) {
        char c = expr[i];
        
        if(c >= 'a' && c <= 'z') {
            output[out_pos++] = c;
        } else if(c == '(') {
            push(c);
        } else if(c == ')') {
            while(top >= 0 && stack[top] != '(') {
                output[out_pos++] = stack[top];
                pop();
            }
            pop(); // Remove '('
        } else if(is_operator(c)) {
            while(top >= 0 && precedence(stack[top]) >= precedence(c)) {
                output[out_pos++] = stack[top];
                pop();
            }
            push(c);
        }
    }
    
    while(top >= 0) {
        output[out_pos++] = stack[top];
        pop();
    }
    output[out_pos] = '\0';
    
    printf("Postfix Expression: %s\n", output);
    
    // Evaluate postfix
    int values[100];
    int val_pos = 0;
    
    printf("\nEvaluating Expression...\n");
    for(int i = 0; i < out_pos; i++) {
        char c = output[i];
        if(c >= 'a' && c <= 'z') {
            printf("Enter value for %c: ", c);
            scanf("%d", &values[val_pos++]);
        } else if(is_operator(c)) {
            int b = values[--val_pos];
            int a = values[--val_pos];
            int result;
            switch(c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            values[val_pos++] = result;
            printf("  %d %c %d = %d\n", a, c, b, result);
        }
    }
    printf("\nResult: %d\n", values[0]);
}
%}

%%

[a-z+*/()-]+      { evaluate(yytext); }

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Operator Precedence Parsing\n");
    printf("Grammar: E->E+E|E-E|E*E|E/E|(E)|id\n");
    printf("\nEnter expression (use a-z variables, +, -, *, /, (, )): ");
    yylex();
    return 0;
}