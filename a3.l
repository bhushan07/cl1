%{
#include <stdio.h>
#include <string.h>
int lno=1;
%}
%%
[0-9]+	{printf("%d	%s	NUMBER\n",lno,yytext);}
[-+*/]	{printf("%d	%s	OPERATORS\n",lno,yytext);}
main|return|include	{printf("%d	%s	KEYWORD\n",lno,yytext);}
\n	{lno++;}
\<	{printf("%d	%s	LESS THAN\n",lno,yytext);}
\>	{printf("%d	%s	GREATER THAN\n",lno,yytext);}
\{	{printf("%d	%s	START OF BLOCK\n",lno,yytext);}
=	{printf("%d	%s	ASSINGNMENT\n",lno,yytext);}
;	{printf("%d	%s	TERMINATOR\n",lno,yytext);}
#	{printf("%d	%s	PREPROCESSOR\n",lno,yytext);}
\}	{printf("%d	%s	END OF BLOCK\n",lno,yytext);}
\[	{printf("%d	%s	SQ OPEN\n",lno,yytext);}
\]	{printf("%d	%s	SQ CLOSE\n",lno,yytext);}
\(	{printf("%d	%s	CR OPEN\n",lno,yytext);}
\)	{printf("%d	%s	CR CLOSE\n",lno,yytext);}
,	{printf("%d	%s	seporator\n",lno,yytext);}
if|for|while	{printf("%d	%s	CONTROL\n",lno,yytext);}
(\"[^\"]*\")	{printf("%d	%s	STRING\n",lno,yytext);}
([a-zA-Z0-9]+\.h)	{printf("%d	%s	HEADER FILE\n",lno,yytext);}
([a-zA-Z][a-zA-Z0-9]*)	{printf("%d	%s	IDENTIFIER\n",lno,yytext);}
%%
int main()
{
char name[100];
printf("enter name:");
scanf("%s",name);

printf("L.NO	LEXEME	TOKEN\n");
yyin=fopen(name,"r");
yylex();

return 0;
}
int yywrap()
{
	return 1;
}
