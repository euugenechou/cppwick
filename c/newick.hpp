#ifndef __NEWICK_HPP__
#define __NEWICK_HPP__

#include "json.hpp"
#include <stdio.h>
#include <string>
#include <vector>

using Json = nlohmann::json;

class NewickTree {
  private:
    double length;
    std::string label;
    std::vector<NewickTree *> *children;

  public:
    NewickTree(const char *label, double length,
               std::vector<NewickTree *> *children);
    ~NewickTree();

    void dump_json(FILE *outfile, int indent = 0);
    void dump_newick(FILE *outfile);

    Json json();
    static NewickTree *from_json(const Json &tree);
    static void annotate(Json &tree, const Json &annotations);
};

#endif
