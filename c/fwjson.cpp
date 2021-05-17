#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include "unistd.h"
#include "json.hpp"

using Json = nlohmann::json;

#define OPTIONS "hi:o:"

void usage(std::ostream &os, char *exec) {
    os << "SYNOPSIS\n"
          "   Geo-genetic visualizer for UShER.\n"
          "\n"
          "USAGE\n";
    os << "   " << exec << " [-h] [-i infile]\n";
    os << "\n"
          "OPTIONS\n"
          "   -h             Print program usage and help.\n"
          "   -c llfile      File of lat/longs for samples.\n"
          "   -i infile      Input MAT protobuf file.\n"
          "   -o outfile     Output of samples in input protobuf.\n"
          "   -s sfile       File of samples."
       << std::endl;
}

int main(int argc, char **argv) {
    int opt = 0;
    std::string infname, outfname, llfname, sfname;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            break;
        case 'i':
            infname = optarg;
            break;
        case 'o':
            outfname = optarg;
            break;
        case 'h':
            usage(std::cout, argv[0]);
            return EXIT_SUCCESS;
        default:
            usage(std::cerr, argv[0]);
            return EXIT_FAILURE;
        }
    }

    std::shared_ptr<std::istream> infile(&std::cin, [](...) {});
    if (infname.length() > 0) {
        infile.reset(new std::ifstream(infname));
    }

    std::shared_ptr<std::ostream> outfile(&std::cout, [](...) {});
    if (outfname.length() > 0) {
        outfile.reset(new std::ofstream(outfname));
    }

    Json tree = Json::parse(*infile);
    *outfile << tree.dump(2) << std::endl;

    return EXIT_SUCCESS;
}
