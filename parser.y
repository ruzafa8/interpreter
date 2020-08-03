%{
	#include"variable.h"
	#include <stdio.h>
	void yyerror (char *);
    extern int yylex();
	Variable *table;
%}

%code requires {
	#include"expression_ast.h"
	
}
%union {
	int integer;
	char * string;
	ExpressionAST * ast;
}
%token PLUS MINUS BY DIV OPEN_PAR CLOSE_PAR ENTER
%token <integer> NUMBER

%token <string> VAR_NAME
%token EQUALS TWO_POINTS

%type <ast> expr expr0 expr1 expr2
%start S
%%

S: expr ENTER{printf("> %d\n",evaluate($1)); return 0;}
 | statements ENTER{return 0;}
 ;
statements: statement statements | statement;
statement: VAR_NAME TWO_POINTS EQUALS expr {	bool inserted = insertVariable($1,evaluate($4),&table);
												if(!inserted) printf("La variable %s no se ha insertado porque ya existía",$1);
										   }
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
     | VAR_NAME {
					int value;
					bool obtenido = valueOf($1,&value,table);
					if(!obtenido) {printf("La variable no existía"); return -1;}
					else $$ = createLeaf(value);
}
     ;
%%

int main() {
	table = createTable();
	while(!yyparse());
	printTable(table);
	return 0;
}
