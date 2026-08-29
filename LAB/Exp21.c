#include <stdio.h>
#include <string.h>

int main()
{
    char s[200];
    int i,count=0;

    printf("Enter sentence: ");
    fgets(s,200,stdin);

    for(i=0;s[i]!='\0';i++)
        if(strchr("aeiouAEIOU",s[i]))
            count++;

    printf("Vowels = %d",count);

    return 0;
}