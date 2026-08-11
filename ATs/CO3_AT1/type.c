#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { INT, FLOAT, PTR } TypeKind;

typedef struct Type {
    TypeKind kind;
    struct Type *subtype;
} Type;

Type *create_basic(TypeKind k) {
    Type *t = malloc(sizeof(Type));
    t->kind = k;
    t->subtype = NULL;
    return t;
}

Type *create_ptr(Type *sub) {
    Type *t = malloc(sizeof(Type));
    t->kind = PTR;
    t->subtype = sub;
    return t;
}

void free_type(Type *t) {
    if (!t) return;
    free_type(t->subtype);
    free(t);
}

Type *parse_type(char **s) {
    while (isspace(**s)) (*s)++;
    Type *t;
    if (strncmp(*s, "int", 3) == 0 && !isalpha((*s)[3])) {
        t = create_basic(INT);
        *s += 3;
    } else if (strncmp(*s, "float", 5) == 0 && !isalpha((*s)[5])) {
        t = create_basic(FLOAT);
        *s += 5;
    } else {
        return NULL;
    }
    while (isspace(**s)) (*s)++;
    if (**s == '*') {
        (*s)++;
        Type *sub = t;
        t = create_ptr(sub);
        while (**s == '*') {
            (*s)++;
            Type *new = create_ptr(t);
            t = new;
        }
    }
    return t;
}

int equivalent(Type *a, Type *b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    if (a->kind != b->kind) return 0;
    if (a->kind == PTR) return equivalent(a->subtype, b->subtype);
    return 1;
}

int main() {
    char input1[100], input2[100];
    printf("Enter first type: ");
    fgets(input1, sizeof(input1), stdin);
    input1[strcspn(input1, "\n")] = 0;
    printf("Enter second type: ");
    fgets(input2, sizeof(input2), stdin);
    input2[strcspn(input2, "\n")] = 0;

    char *p1 = input1, *p2 = input2;
    Type *t1 = parse_type(&p1);
    Type *t2 = parse_type(&p2);

    if (!t1 || !t2) {
        printf("Invalid type expression\n");
        return 1;
    }

    if (equivalent(t1, t2))
        printf("Equivalent\n");
    else
        printf("Not equivalent\n");

    free_type(t1);
    free_type(t2);
    return 0;
}