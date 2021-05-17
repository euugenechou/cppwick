#include "reader.hpp"

Flywick::Reader::~Reader() {
    delete lexer;
    lexer = nullptr;
    delete parser;
    parser = nullptr;
}

NewickTree *Flywick::Reader::parse(std::istream &is) {
    lexer = new Flywick::Lexer(&is);
    parser = new Flywick::Parser(*lexer, &root);

    if (parser->parse() != 0) {
        std::cerr << "Error: parsing failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    return root;
}
