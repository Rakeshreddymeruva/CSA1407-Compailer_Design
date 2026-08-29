#include <stdio.h>

int main()
{
    char a,b,op;

    printf("Enter expression: ");
    scanf(" %c %c %c",&a,&op,&b);

    printf("MOV R1, %c\n",a);

    if(op=='+')
        printf("ADD R1, %c\n",b);
    else if(op=='-')
        printf("SUB R1, %c\n",b);
    else if(op=='*')
        printf("MUL R1, %c\n",b);
    else if(op=='/')
        printf("DIV R1, %c\n",b);

    printf("MOV RESULT, R1\n");

    return 0;
}