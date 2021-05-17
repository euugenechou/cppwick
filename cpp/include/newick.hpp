#ifndef __NEWICK_HPP__
#define __NEWICK_HPP__

#include "json.hpp"
#include <stdio.h>
#include <string>
#include <vector>

using Json = nlohmann::json;

class NewickTree {
  public:
    double length;
    std::string label;
    std::vector<NewickTree *> *children;

    NewickTree(std::string *label, double length,
               std::vector<NewickTree *> *children);
    ~NewickTree();

    Json to_json();
    static NewickTree *from_json(const Json &tree);
    static void annotate_json(Json &tree, const Json &annotations);

    void dump_json(FILE *outfile, int indent = 0);
    void dump_newick(FILE *outfile);
};

#endif
