#include "json.hpp"
#include "newick.hpp"
#include "unistd.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using Json = nlohmann::json;

#define OPTIONS "ha:i:o:"

void usage(std::ostream &os, char *exec) {
    os << "SYNOPSIS\n"
          "   JSON Newick tree annotator.\n"
          "\n"
          "USAGE\n";
    os << "   " << exec << " [-h] -a afile [-i infile] [-o outfile]\n";
    os << "\n"
          "OPTIONS\n"
          "   -h             Print program usage and help.\n"
          "   -a afile       File of JSON annotations.\n"
          "   -i infile      Input JSON Newick tree.\n"
          "   -o outfile     Output of annotated JSON Newick tree.\n"
       << std::endl;
}

int main(int argc, char **argv) {
    int opt = 0;
    std::string afname, ifname, ofname;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            afname = optarg;
            break;
        case 'i':
            ifname = optarg;
            break;
        case 'o':
            ofname = optarg;
            break;
        case 'h':
            usage(std::cout, argv[0]);
            return EXIT_SUCCESS;
        default:
            usage(std::cerr, argv[0]);
            return EXIT_FAILURE;
        }
    }

    std::ifstream as(afname);
    if (as.fail()) {
        std::cerr << "Error: failed to open " << afname << std::endl;
        return EXIT_FAILURE;
    }

    std::shared_ptr<std::istream> is(&std::cin, [](...) {});
    if (ifname.length() > 0) {
        is.reset(new std::ifstream(ifname));
    }

    std::shared_ptr<std::ostream> os(&std::cout, [](...) {});
    if (ofname.length() > 0) {
        os.reset(new std::ofstream(ofname));
    }

    Json tree = Json::parse(*is);
    Json annotations = Json::parse(as);
    NewickTree::annotate(tree, annotations);
    *os << tree.dump(2) << std::endl;

    return EXIT_SUCCESS;
}
