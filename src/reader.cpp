#include "reader.hpp"

Flywick::Reader::~Reader() {
    delete lexer;
    lexer = nullptr;
    delete parser;
    parser = nullptr;
    delete root;
    root = nullptr;
}

NewickTree *Flywick::Reader::parse(std::istream &is) {
    try {
        lexer = new Flywick::Lexer(&is);
    } catch (std::bad_alloc &err) {
        std::cerr << "Error: " << err.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
        parser = new Flywick::Parser(*lexer, &root);
    } catch (std::bad_alloc &err) {
        std::cerr << "Error: " << err.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (parser->parse() != 0) {
        std::cerr << "Error: parsing failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    return root;
}
