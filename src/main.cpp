#include "parser.hh"

#include <iostream>

int main (int argc, char *argv[]) {
    std::cout << "Enter text: ";
    std::string input;
    std::getline(std::cin, input);

    Parser parse;

    std::cout << parse.parse<std::string>(input) << std::endl;
    return 0;
}
