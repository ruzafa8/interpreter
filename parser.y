%{
	#include <stdio.h>
	void yyerror (char *);
    extern int yylex();
%}

%code requires {
	#include"expression_ast.h"
}
%union {
	int integer;
	ExpressionAST * ast;
}
%token PLUS MINUS BY DIV OPEN_PAR CLOSE_PAR ENTER
%token <integer> NUMBER

%type <ast> expr expr0 expr1 expr2
%start S
%%

S: expr ENTER {printf("> %d\n",evaluate($1)); return 0;}
 ;

expr: expr PLUS expr0  {$$ = createBinary(PLUS_OP,$1, $3);}
    | expr MINUS expr0 {$$ = createBinary(MINUS_BINARY_OP,$1, $3);}
    | expr0 {$$ = $1;}
    ;

expr0: expr0 BY expr1  {$$ = createBinary(BY_OP,$1, $3);}
     | expr0 DIV expr1 {$$ = createBinary(DIV_OP,$1, $3);}
     | expr1 {$$ = $1;}
     ;

expr1: MINUS expr1 {$$ = createUnary(MINUS_UNARY_OP, $2);}
     | expr2 {$$ = $1;}
     ;

expr2: OPEN_PAR expr CLOSE_PAR {$$ = $2;}
     | NUMBER {$$ = createLeaf($1);}
     ;
%%

int main() {
	while(!yyparse());
	return 0;
}
