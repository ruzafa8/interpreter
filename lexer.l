%{
	#include "y.tab.h"
%}

DIGIT  [[:digit:]]
DIGITS {DIGIT}+

%%
{DIGITS}  {yylval.integer = atoi(yytext); return NUMBER;}
"("       return OPEN_PAR;
")"       return CLOSE_PAR;
"+"       return PLUS;
"-"       return MINUS;
"*"       return BY;
"/"       return DIV;
\n        return ENTER;
.         //Do nothing

%%

