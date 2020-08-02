%{
	#include <stdio.h>
	void yyerror (char *);
    extern int yylex();
%}
%union {
	int integer;
}
%token PLUS MINUS BY DIV
%token <integer> NUMBER
%start S
%%

S: expr {printf("\nOPERACIÓN CALCULADA\n");return 0;}
 ;

expr: NUMBER PLUS NUMBER   {printf("%d", $1 + $3);}
    | NUMBER MINUS NUMBER  {printf("%d", $1 - $3);}
    | NUMBER BY NUMBER     {printf("%d", $1 * $3);}
    | NUMBER DIV NUMBER    {printf("%d", $1 / $3);}
    ;
%%

int main() {
	return yyparse();
}
