#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#ifndef yyFlexLexerOnce
#include "FlexLexer.h"
#endif

#include "parser.tab.hh"

namespace Flywick {
class Lexer : public yyFlexLexer {
  private:
    Flywick::Parser::semantic_type *yylval = nullptr;

  public:
    Lexer(std::istream *is) : yyFlexLexer(is){};
    virtual ~Lexer(){};

    using FlexLexer::yylex;
    virtual int yylex(Flywick::Parser::semantic_type *lval);
};
} // namespace Flywick

#endif
