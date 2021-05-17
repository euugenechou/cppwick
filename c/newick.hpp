#ifndef __NEWICK_HPP__
#define __NEWICK_HPP__

#include <string>
#include <vector>
#include <stdio.h>
#include "json.hpp"

using Json = nlohmann::json;

class NewickTree {
private:
    double length;
    std::string label;
    std::vector<NewickTree *> *children;

public:
    NewickTree(const char *label, double length, std::vector<NewickTree *> *children);
    ~NewickTree();

    void dump_json(FILE *outfile, int indent = 0);
    void dump_newick(FILE *outfile);

    Json json();
    friend NewickTree *newick_from_json(Json &tree);
};

NewickTree *newick_from_json(Json &tree);

#endif
