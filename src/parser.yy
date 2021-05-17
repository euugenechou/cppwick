%require "3.7.6"
%skeleton "lalr1.cc"

%defines
%define api.namespace {Flywick}
%define api.parser.class {Parser}

%code requires {
    #ifndef YY_NULLPTR
    #   if defined __cplusplus && 201102L <= __cplusplus
    #       define YY_NULLPTR nullptr
    #   else
    #       define YY_NULLPTR 0
    #   endif
    #endif

    #include <string>
    #include <tuple>
    #include <vector>

    namespace Flywick {
        class Lexer;
        class Reader;
    }

    class NewickTree;
}

%code {
    #include "reader.hpp"
    #include "newick.hpp"
    #include <cstdlib>
    #include <fstream>
    #include <iostream>

    #undef yylex
    #define yylex lexer.yylex
}

%parse-param {Lexer &lexer}
%parse-param {NewickTree **root}

%define parse.assert

%locations

%union {
    std::string *label;
    double length;
    NewickTree *tree;
    std::tuple<std::string *, double> *info;
    std::vector<NewickTree *> *children;
}

%token<label> LABEL
%token<length> LENGTH

%type<tree> newick
%type<tree> node
%type<children> subtree
%type<info> info
%type<children> children
%type<label> label
%type<length> length

%%
newick
    : node ';' { *root = $1; }
    ;

node
    : subtree info {
        $$ = new NewickTree(std::get<0>(*$2), std::get<1>(*$2), $1);
        delete std::get<0>(*$2);
        delete $2;
    }
    ;

subtree
    : '(' children ')'  { $$ = $2; }
    |                   { $$ = new std::vector<NewickTree *>(); }
    ;

info
    : label         { $$ = new std::tuple<std::string *, double>{ $1, -1.0 }; }
    | length        { $$ = new std::tuple<std::string *, double>{ new std::string(""), $1 }; }
    | label length  { $$ = new std::tuple<std::string *, double>{ $1, $2 }; }
    |               { $$ = new std::tuple<std::string *, double>{ new std::string(""), -1.0 }; }
    ;

children
    : node              { $$ = new std::vector<NewickTree *>{$1}; }
    | children ',' node { $$ = $1; $$->push_back($3); }
    ;

label
    : LABEL { $$ = $1; }
    ;

length
    : LENGTH { $$ = $1; }
    ;
%%

void Flywick::Parser::error(const location_type &loc,
                            const std::string &err) {
    std::cerr << "Error: " << err << " at " << loc << std::endl;
}
