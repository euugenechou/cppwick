#include "lexyacc.hpp"
#include "yyparse.hpp"
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hnji:o:"

void usage(FILE *out, char *exec) {
    fprintf(out,
            "SYNOPSIS\n"
            "  A fast Flex/Yacc-based Newick tree format parser.\n"
            "\n"
            "USAGE\n"
            "  %s [-h] [-i infile] [-o outfile]\n"
            "\n"
            "OPTIONS\n"
            "  -h           Program usage and help.\n"
            "  -n           Output parsed tree in the Newick format.\n"
            "  -j           Output parsed tree as JSON.\n"
            "  -i infile    Specify input containing Newick tree.\n"
            "  -o outfile   Specify output of pretty-printed tree.\n",
            exec);
}

int main(int argc, char **argv) {
    int opt = 0;
    bool json = false, newick = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            yyin = fopen(optarg, "r");
            if (!yyin) {
                fprintf(stderr, "Error: can't open %s.\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 'o':
            yyout = fopen(optarg, "w");
            if (!yyout) {
                fprintf(stderr, "Error: can't open %s.\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 'j':
            json = true;
            break;
        case 'n':
            newick = true;
            break;
        case 'h':
            usage(stdout, argv[0]);
            return EXIT_SUCCESS;
        default:
            usage(stderr, argv[0]);
            return EXIT_FAILURE;
        }
    }

    NewickTree *root = nullptr;

    if (yyparse(&root) == 0) {
        if (json) root->dump_json(yyout, 2);
        if (newick) root->dump_newick(yyout);
    } else {
        fprintf(stderr, "Error: invalid Newick format.\n");
    }

    delete root;
    fclose(yyin);
    fclose(yyout);
    yylex_destroy();
    return EXIT_SUCCESS;
}
