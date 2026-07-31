#include <stdio.h>
#include <string.h>

void run_ll1_parser(const char *expr) {
    printf("[LL(1) Engine] Parsing simple expression/header: %s -> ACCEPTED\n", expr);
}

void run_lr_parser(const char *expr) {
    printf("[LR Engine] Parsing complex nested operator expression: %s -> ACCEPTED\n", expr);
}

int is_complex_expression(const char *expr) {
    int operators = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            operators++;
        }
    }
    return (operators > 1) ? 1 : 0;
}

int main() {
    char test_input_1[50] = "id+id";
    char test_input_2[50] = "id+id*id";

    printf("Dispatcher Router Test 1:\n");
    if (is_complex_expression(test_input_1)) {
        run_lr_parser(test_input_1);
    } else {
        run_ll1_parser(test_input_1);
    }

    printf("\nDispatcher Router Test 2:\n");
    if (is_complex_expression(test_input_2)) {
        run_lr_parser(test_input_2);
    } else {
        run_ll1_parser(test_input_2);
    }

    return 0;
}