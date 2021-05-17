%{
  #include <string>
  #include "lexer.hpp"

  #undef YY_DECL
  #define YY_DECL int Flywick::Lexer::yylex(Flywick::Parser::semantic_type *lval, Flywick::Parser::location_type *loc)

  #define YY_NO_UNISTD_H
  #define YY_USER_ACTION loc->step(); loc->columns(yyleng);

  using token = Flywick::Parser::token;
%}

%option yyclass="Flywick::FlywickLexer"
%option noyywrap
%option noinput
%option nounput
%option c++

label       ([^\,\;\:\(\)\[\]]+)
length      (:([0-9]+\.?[0-9]+([Ee]-?[0-9]+)?|[0-9]+))
whitespace  ([ \t]+)

%%
%{          
  yylval = lval;
%}

{whitespace}  ;
"\n"          ;

","   { return ','; }
":"   { return ':'; }
";"   { return ';'; }
"("   { return '('; }
")"   { return ')'; }

{label} {
  yylval->label = new std::string(yytext);
  return token::LABEL;
}

{length} {
  yylval->length = std::stod(yytext + 1);
  return token::LENGTH; 
}

. ;
%%
