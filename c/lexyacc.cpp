#include "lexyacc.hpp"
#include <iostream>

int yyerror(NewickTree **root, const char *msg) {
    std::cerr << "Error: " << msg << std::endl;
    return 1;
}
