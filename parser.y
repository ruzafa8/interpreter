%{
	#include"variable.h"
	void yyerror (char *);
    extern int yylex();
	Variable *table;
%}

%code requires {
	#include"statement_ast.h"
}
%union {
	int integer;
	char * string;
	ExpressionAST * exp;
	StatementAST * st;
}
%token PLUS MINUS BY DIV OPEN_PAR CLOSE_PAR FIN
%token <integer> NUMBER

%token <string> VAR_NAME
%token EQUALS TWO_POINTS PRINT

%type <exp> expr expr0 expr1 expr2

%type <st> statement statements
%start S
%%

S: statements FIN{execute($1,&table); return 0;}
 ;
statements: statement {$$ = $1;}
          | statement statements {$$ = createDoubleSt($1,$2);}
          ;
statement: VAR_NAME EQUALS expr {$$ = createAsigSt($1,$3);}
         | VAR_NAME TWO_POINTS EQUALS expr {$$ = createDeclAsigSt($1,$4);} 
         | PRINT expr {$$ = createPrintSt($2);}
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
     | VAR_NAME {$$ = createVariable($1);}
     ;
%%

int main() {
	table = createTable();
	yyparse();
	printTable(table);
	return 0;
}
