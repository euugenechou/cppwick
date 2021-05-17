#include "reader.hpp"
#include <cstdlib>
#include <iostream>

int main(void) {
    Flywick::Reader reader;
    NewickTree *root = reader.parse(std::cin);
    std::cout << root->to_json().dump(2) << std::endl;
    return 0;
}
