%{
#include "yyparse.hpp"
#include <iostream>
%}


label       ([^\,\;\:\(\)\[\]]+)
length      (:([0-9]+\.?[0-9]+([Ee]-?[0-9]+)?|[0-9]+))
whitespace  ([ \t]+)

%option noyywrap
%option noinput
%option nounput

%%
{whitespace}  ;
"\n"          ;

","           { return ','; }
":"           { return ':'; }
";"           { return ';'; }
"("           { return '('; }
")"           { return ')'; }

{label}       { yylval.label = strdup(yytext); return LABEL; }
{length}      { yylval.length = std::stod(yytext + 1); return LENGTH; }

.             ;
%%
