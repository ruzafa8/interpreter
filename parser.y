%{
	#include <stdio.h>
	void yyerror (char *);
    extern int yylex();
%}
%union {
	int integer;
}
%token PLUS MINUS BY DIV OPEN_PAR CLOSE_PAR ENTER
%token <integer> NUMBER

%type <integer> expr expr0 expr1 expr2
%start S
%%

S: expr ENTER {printf("> %d\n",$1); return 0;}
 ;

expr: expr PLUS expr0  {$$ = $1 + $3;}
    | expr MINUS expr0 {$$ = $1 - $3;}
    | expr0 {$$ = $1;}
    ;

expr0: expr0 BY expr1  {$$ = $1 * $3;}
     | expr0 DIV expr1 {$$ = $1 / $3;}
     | expr1 {$$ = $1;}
     ;

expr1: MINUS expr1 {$$ = -$2;}
     | expr2 {$$ = $1;}
     ;

expr2: OPEN_PAR expr CLOSE_PAR {$$ = $2;}
     | NUMBER {$$ = $1;}
     ;
%%

int main() {
	while(!yyparse());
	return 0;
}
