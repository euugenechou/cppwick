#ifndef __LEXYACC_HPP__
#define __LEXYACC_HPP__

#include "newick.hpp"

extern FILE *yyin;
extern FILE *yyout;

int yylex(void);

int yyparse(NewickTree **root);

int yylex_destroy(void);

int yyerror(NewickTree **root, const char *msg);

#endif
