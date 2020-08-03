%{
	#include "y.tab.h"
%}

DIGIT  [[:digit:]]
DIGITS {DIGIT}+

LITERAL [[:alpha:]]
LITERALS {LITERAL}+

%%

{DIGITS}  {yylval.integer = atoi(yytext); return NUMBER;}
"("       return OPEN_PAR;
")"       return CLOSE_PAR;
"+"       return PLUS;
"-"       return MINUS;
"*"       return BY;
"/"       return DIV;
"\n"	  return ENTER;
":"       return TWO_POINTS;
"="       return EQUALS;
"print"   return PRINT;


{LITERALS} {yylval.string = strdup(yytext); return VAR_NAME;}

.         //Do nothing

%%
