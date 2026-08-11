#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *expr;
char lookahead;

void next() { lookahead = *expr++; }

double E();
double E_prime(double left);
double T();
double T_prime(double left);
double F();
double var_val(char c);

double E() {
    double left = T();
    return E_prime(left);
}

double E_prime(double left) {
    if (lookahead == '+') {
        next();
        double right = T();
        return E_prime(left + right);
    } else if (lookahead == '-') {
        next();
        double right = T();
        return E_prime(left - right);
    } else {
        return left;
    }
}

double T() {
    double left = F();
    return T_prime(left);
}

double T_prime(double left) {
    if (lookahead == '*') {
        next();
        double right = F();
        return T_prime(left * right);
    } else if (lookahead == '/') {
        next();
        double right = F();
        return T_prime(left / right);
    } else {
        return left;
    }
}

double F() {
    if (lookahead == '(') {
        next();
        double val = E();
        if (lookahead == ')') next();
        return val;
    } else if (isalpha(lookahead)) {
        double val = var_val(lookahead);
        next();
        return val;
    }
    return 0;
}

double var_val(char c) {
    if (c == 'a') return 1;
    if (c == 'b') return 2;
    if (c == 'c') return 3;
    return 0;
}

int main() {
    char input[100];
    printf("Enter expression (e.g., a+b*c): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    expr = input;
    next();
    double result = E();
    printf("Result: %g\n", result);
    return 0;
}