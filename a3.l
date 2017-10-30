%{
#include <stdio.h>
#include <string.h>
int lno=1;
%}
%%
[0-9]+	{printf("%d \t\t %s \t\t NUMBER\n",lno,yytext); }
[-+*/]	{printf("%d \t\t %s \t\t OPERATOR\n",lno,yytext); }
=	{printf("%d \t\t %s \t\t ASSIGNMENT\n",lno,yytext); }
include|main|return	{printf("%d \t\t %s \t\t KEYWORD\n",lno,yytext);}
int|float|char|double	{printf("%d \t\t %s \t\t DATATYPE\n",lno,yytext);}
\n	{lno++;}
if|for|while	{printf("%d \t\t %s \t\t CONTROL STATEMENT \n",lno,yytext);}
#	{printf("%d \t\t %s \t\t PREPROCESSOR\n",lno,yytext);}
;	{printf("%d \t\t %s \t\t TERMINATOR\n",lno,yytext);}
\<	{printf("%d \t\t %s \t\t LESS THAN\n",lno,yytext);}
\>	{printf("%d \t\t %s \t\t GREATER THAN\n",lno,yytext);}
\{	{printf("%d \t\t %s \t\t START OF BLOCK\n",lno,yytext);}
\}	{printf("%d \t\t %s \t\t END OF BLOCK\n",lno,yytext);}
\(	{printf("%d \t\t %s \t\t OPEN\n",lno,yytext);}
\)	{printf("%d \t\t %s \t\t CLOSE\n",lno,yytext);}
\[	{printf("%d \t\t %s \t\t OPEN\n",lno,yytext);}
\]	{printf("%d \t\t %s \t\t CLOSE\n",lno,yytext);}
,	{printf("%d \t\t %s \t\t SEPARATOR\n",lno,yytext);}
printf|scanf	{printf("%d \t\t %s \t\t LIBRARY FUNCTION\n",lno,yytext);}
(\"[^\"]*\")	{printf("%d \t\t %s \t\t STRING CONSTANT\n",lno,yytext);}
([a-zA-Z0-9]+\.h) {printf("%d \t\t %s \t\t HEADER FILE\n",lno,yytext);}
[a-zA-Z][a-zA-Z0-9]* {printf("%d \t\t %s \t\t IDENTIFIER\n",lno,yytext);}
%%
int main()
{
char ifile[100];
printf("\nEnter input file name: ");
scanf("%s",ifile);
yyin=fopen(ifile,"r");
printf("Line No \t LEXEME \t Token\n");
yylex();
return 0;
}
int yywrap()
{
return 1;
}
