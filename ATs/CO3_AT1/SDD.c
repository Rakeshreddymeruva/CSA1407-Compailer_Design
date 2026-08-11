#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *input;
double E();
double T();
double F();

double E() {
    double val = T();
    while (*input == '+' || *input == '-') {
        char op = *input++;
        double rhs = T();
        if (op == '+') val += rhs;
        else val -= rhs;
    }
    return val;
}

double T() {
    double val = F();
    while (*input == '*' || *input == '/') {
        char op = *input++;
        double rhs = F();
        if (op == '*') val *= rhs;
        else val /= rhs;
    }
    return val;
}

double F() {
    double val;
    if (*input == '(') {
        input++;
        val = E();
        if (*input == ')') input++;
    } else {
        char *end;
        val = strtod(input, &end);
        input = end;
    }
    return val;
}

int main() {
    char expr[100];
    printf("Enter expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0;
    input = expr;
    double result = E();
    printf("Result: %g\n", result);
    return 0;
}