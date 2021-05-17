#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include "lexer.hpp"
#include "newick.hpp"
#include "parser.tab.hh"
#include <cstddef>
#include <string>

namespace Flywick {
class Reader {
  private:
    Flywick::Lexer *lexer = nullptr;
    Flywick::Parser *parser = nullptr;

  public:
    NewickTree *root = nullptr;

    Reader() = default;
    virtual ~Reader();

    NewickTree *parse(std::istream &is);
};
} // namespace Flywick

#endif
