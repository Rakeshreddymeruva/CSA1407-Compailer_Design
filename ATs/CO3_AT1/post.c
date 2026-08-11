#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

double stack[MAX];
int top = -1;

void push(double v) { stack[++top] = v; }
double pop() { return stack[top--]; }

int main() {
    char expr[200];
    printf("Enter postfix expression (space separated): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0;
    char *token = strtok(expr, " ");
    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(atof(token));
        } else {
            double b = pop();
            double a = pop();
            double res;
            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                default: res = 0;
            }
            push(res);
            printf("Intermediate: %g\n", res);
        }
        token = strtok(NULL, " ");
    }
    printf("Final result: %g\n", pop());
    return 0;
}