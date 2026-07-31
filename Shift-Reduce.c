#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void check(char *input, int *i) {
    while (1) {
        if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '+' && stack[top] == 'E') {
            if (input[*i] == '*') {
                break;
            }
            top -= 2;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduce: E -> E + E\t\t");
            printf("%s\t\t$%s\n", &input[*i], stack);
        } else if (top >= 2 && stack[top-2] == 'E' && stack[top-1] == '*' && stack[top] == 'E') {
            top -= 2;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduce: E -> E * E\t\t");
            printf("%s\t\t$%s\n", &input[*i], stack);
        } else if (top >= 1 && stack[top-1] == 'i' && stack[top] == 'd') {
            top -= 1;
            stack[top] = 'E';
            stack[top+1] = '\0';
            printf("Reduce: E -> id\t\t\t");
            printf("%s\t\t$%s\n", &input[*i], stack);
        } else {
            break;
        }
    }
}

int main() {
    char input[50] = "id+id*id$";
    int i = 0;
    push('$');

    printf("Action\t\t\tInput Buffer\tStack\n");
    printf("------\t\t\t-----------------\-----\n");

    while (input[i] != '$') {
        if (input[i] == 'i' && input[i+1] == 'd') {
            push('i');
            push('d');
            i += 2;
            printf("Shift (id)\t\t");
            printf("%s\t\t$%s\n", &input[i], stack);
            check(input, &i);
        } else {
            push(input[i]);
            printf("Shift (%c)\t\t", input[i]);
            i++;
            printf("%s\t\t$%s\n", &input[i], stack);
            check(input, &i);
        }
    }
    
    check(input, &i);

    if (top == 1 && stack[1] == 'E') {
        printf("\nResult: String Accepted Successfully!\n");
    } else {
        printf("\nResult: String Rejected!\n");
    }

    return 0;
}