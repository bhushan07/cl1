%{
	#include<stdio.h>
	#include<stdlib.h>
	#include "y.tab.h"
	extern FILE* yyin;
	void yyerror(char *s);
	int yylex();
%}
%token HEADER MAIN OPB CLB STARTB ENDB ENDS EQ DT DIGIT ID PLUS 
%%
S: Preprocessor MAIN {printf("main block\n");} STARTB Statement ENDB {printf("main block terminated\n");};
Preprocessor: HEADER Preprocessor | HEADER {printf("PreProcessor Statement\n");};
Statement: stmt | Statement stmt | Statement exp;
exp: ID EQ ID PLUS ID ENDS {printf("PLus Statement\n");};
stmt: DT ID ENDS {printf("Statement\n");}| assignment ;
assignment: DT ID EQ DIGIT ENDS {printf("Assignment Statement\n");};
%%

void yyerror(char *s)
{
	printf("error %s",s);
}

int main()
{
	yyin=fopen("sample.c","r");
	yyparse();
	return 0;
}
