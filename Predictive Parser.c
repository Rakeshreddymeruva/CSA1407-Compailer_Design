#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

void pop() {
    top--;
}

char peek() {
    if (top >= 0)
        return stack[top];
    return '\0';
}

void displayStack() {
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
}

int main() {
    char input[100] = "id + id * id $";
    int i = 0;

    push('$');
    push('E');

    printf("Stack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");

    while (top >= 0) {
        printf("$");
        for(int k=1; k<=top; k++) printf("%c", stack[k]);
        printf("\t\t%s\t\t", &input[i]);

        char t = peek();
        char curr = input[i];

        if (t == curr) {
            if (t == '$') {
                printf("Accepted\n");
                break;
            }
            printf("Match %c\n", curr);
            pop();
            i += (curr == 'i') ? 3 : 2; 
        } else if (t == 'E') {
            printf("E -> T E'\n");
            pop();
            push('e'); 
            push('T');
        } else if (t == 'e') {
            if (curr == '+') {
                printf("E' -> + T E'\n");
                pop();
                push('e');
                push('T');
                push('+');
            } else {
                printf("E' -> epsilon\n");
                pop();
            }
        } else if (t == 'T') {
            printf("T -> F T'\n");
            pop();
            push('t');
            push('F');
        } else if (t == 't') {
            if (curr == '*') {
                printf("T' -> * F T'\n");
                pop();
                push('t');
                push('F');
                push('*');
            } else {
                printf("T' -> epsilon\n");
                pop();
            }
        } else if (t == 'F') {
            if (curr == 'i') {
                printf("F -> id\n");
                pop();
                push('d');
                push('i');
            } else {
                printf("Error\n");
                break;
            }
        } else if (t == 'i') {
            pop();
        } else if (t == 'd') {
            pop();
        } else {
            printf("Error\n");
            break;
        }
    }
    return 0;
}