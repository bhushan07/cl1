%{
	#include<stdio.h>
	#include "y.tab.h"
	extern int yylval;
%}

%%
"#include<"[a-zA-Z]+".h>"[\n]* {return HEADER;}
"main()"[\n]* {return MAIN;}
"(" {return OPB;}
")" {return CLB;}
"{"[\n]* {return STARTB;}
"}"[\n]* {return ENDB;}
";"[\n]* {return ENDS;}
"=" {return EQ;}
"+" {return PLUS;}
int|float|char|double {return DT;}
[0-9]+ {yylval=atoi(yytext); return DIGIT;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
[\t]+ ;
%%

int yywrap()
{
	return 1;
}

/*
#include<stdio.h>
main()
{
	int b;
	int c=2;
	int d=1;
	b=c+d;
}*/
