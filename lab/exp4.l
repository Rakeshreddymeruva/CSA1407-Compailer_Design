%{
#include <stdio.h>
%}

%%

"+"               { printf("%s is Addition operator\n", yytext); }
"-"               { printf("%s is Subtraction operator\n", yytext); }
"*"               { printf("%s is Multiplication operator\n", yytext); }
"/"               { printf("%s is Division operator\n", yytext); }
"%"               { printf("%s is Modulus operator\n", yytext); }
"="               { printf("%s is Assignment operator\n", yytext); }
"=="              { printf("%s is Equal to operator\n", yytext); }
"!="              { printf("%s is Not Equal operator\n", yytext); }
"<"               { printf("%s is Less than operator\n", yytext); }
">"               { printf("%s is Greater than operator\n", yytext); }
"<="              { printf("%s is Less than or Equal operator\n", yytext); }
">="              { printf("%s is Greater than or Equal operator\n", yytext); }
"&&"              { printf("%s is Logical AND operator\n", yytext); }
"||"              { printf("%s is Logical OR operator\n", yytext); }
"!"               { printf("%s is Logical NOT operator\n", yytext); }
"&"               { printf("%s is Bitwise AND operator\n", yytext); }
"|"               { printf("%s is Bitwise OR operator\n", yytext); }
"^"               { printf("%s is Bitwise XOR operator\n", yytext); }
"~"               { printf("%s is Bitwise NOT operator\n", yytext); }
"<<"              { printf("%s is Left shift operator\n", yytext); }
">>"              { printf("%s is Right shift operator\n", yytext); }
"++"              { printf("%s is Increment operator\n", yytext); }
"--"              { printf("%s is Decrement operator\n", yytext); }

[ \t\n]+          { /* Ignore whitespace */ }
.                 { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter operators: ");
    yylex();
    return 0;
}