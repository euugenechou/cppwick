#include "reader.hpp"
#include <cstdlib>
#include <iostream>

int main(void) {
    std::ios::sync_with_stdio(false);
    Flywick::Reader reader;
    NewickTree *root = reader.parse(std::cin);
    return 0;
}
