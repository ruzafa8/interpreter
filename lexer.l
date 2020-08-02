%{
	#include "y.tab.h"
%}

DIGIT  [[:digit:]]
DIGITS {DIGIT}+

%%
{DIGITS}  {yylval.integer = atoi(yytext); return NUMBER;}
"+"       return PLUS;
"-"       return MINUS;
"*"       return BY;
"/"       return DIV;
.         //Do nothing

%%

