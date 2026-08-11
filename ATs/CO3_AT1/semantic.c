#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum { INT, FLOAT, CHAR, PTR } TypeKind;

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
    } else if (strncmp(*s, "char", 4) == 0 && !isalpha((*s)[4])) {
        t = create_basic(CHAR);
        *s += 4;
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

int is_numeric(Type *t) {
    if (!t) return 0;
    if (t->kind == PTR) return 0;
    return (t->kind == INT || t->kind == FLOAT);
}

int is_valid_operator(char op, Type *a, Type *b) {
    if (op != '+' && op != '*') return 0;
    return (is_numeric(a) && is_numeric(b));
}

int main() {
    char type1[100], type2[100], op;
    printf("Enter first type: ");
    fgets(type1, sizeof(type1), stdin);
    type1[strcspn(type1, "\n")] = 0;
    printf("Enter operator (+,*): ");
    scanf(" %c", &op);
    getchar();
    printf("Enter second type: ");
    fgets(type2, sizeof(type2), stdin);
    type2[strcspn(type2, "\n")] = 0;

    char *p1 = type1, *p2 = type2;
    Type *t1 = parse_type(&p1);
    Type *t2 = parse_type(&p2);

    if (!t1 || !t2) {
        printf("Invalid type\n");
        return 1;
    }

    if (is_valid_operator(op, t1, t2))
        printf("Valid expression\n");
    else
        printf("Type error\n");

    free_type(t1);
    free_type(t2);
    return 0;
}