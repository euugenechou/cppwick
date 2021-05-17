%require "3.7.6"

%{
#include "lexyacc.hpp"
%}

%code requires {
#include <tuple>
#include <vector>
}

%union {
    char *label;
    double length;
    class NewickTree *tree;
    std::tuple<char *, double> *info;
    std::vector<class NewickTree *> *children;
};

%token<label> LABEL
%token<length> LENGTH

%type<tree> newick
%type<tree> node
%type<children> subtree
%type<info> info
%type<children> children
%type<label> label
%type<length> length

%parse-param {NewickTree **root}

%%
newick
    : node ';' { *root = $1; }
    ;

node
    : subtree info {
        $$ = new NewickTree(std::get<0>(*$2), std::get<1>(*$2), $1);
        free(std::get<0>(*$2));
        delete $2;
    }
    ;

subtree
    : '(' children ')'  { $$ = $2; }
    |                   { $$ = new std::vector<NewickTree *>(); }
    ;

info
    : label         { $$ = new std::tuple<char *, double>{ $1, -1.0 }; }
    | length        { $$ = new std::tuple<char *, double>{ strdup(""), $1 }; }
    | label length  { $$ = new std::tuple<char *, double>{ $1, $2 }; }
    |               { $$ = new std::tuple<char *, double>{ strdup(""), -1.0 }; }
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
