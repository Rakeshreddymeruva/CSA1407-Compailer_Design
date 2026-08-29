#include <stdio.h>
#include <string.h>

int main()
{
    char s[100];

    printf("Enter expression: ");
    scanf("%s",s);

    printf("LEADING: ");

    if(s[0]=='(')
        printf("( ");

    if(strncmp(s,"id",2)==0)
        printf("id ");

    printf("\n");

    return 0;
}