#include <stdio.h>

int main()
{
    FILE *in, *out;
    char input[50], output[50];
    char c, next;

    printf("Enter input C file: ");
    scanf("%s", input);

    printf("Enter output C file: ");
    scanf("%s", output);

    in = fopen(input, "r");
    out = fopen(output, "w");

    if(in == NULL || out == NULL)
    {
        printf("File error");
        return 0;
    }

    while((c = fgetc(in)) != EOF)
    {
        if(c == '/')
        {
            next = fgetc(in);

            if(next == '/')
            {
                while((c = fgetc(in)) != '\n' && c != EOF);
            }
            else if(next == '*')
            {
                while((c = fgetc(in)) != EOF)
                {
                    if(c == '*')
                    {
                        next = fgetc(in);
                        if(next == '/')
                            break;
                    }
                }
            }
            else
            {
                fputc(c, out);
                fputc(next, out);
            }
        }
        else
        {
            fputc(c, out);
        }
    }

    fclose(in);
    fclose(out);

    printf("Comments removed");

    return 0;
}