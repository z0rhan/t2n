#include "parser.hh"
#include "error.hh"

#include <iostream>

int main (int argc, char *argv[]) {
    std::string inputFile = "test.txt";


    try {
        Parser::parseFile(inputFile);
    }
    catch (ParseError const& ex) {
        std::cout << "ParseError: " << ex.what() << std::endl;
    }

    std::cout << Parser::parseNumber<int>("one hundred one") << std::endl;
    std::cout << Parser::parseNumber<float>("one hundred one point one two") << std::endl;

    return 0;
}
