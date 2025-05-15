#include "parser.hh"
#include "error.hh"

#include <iostream>

int main (int argc, char *argv[]) {
    std::string inputFile = "test.txt";

    Parser* parse = new Parser();

    try {
        parse->parseFile(inputFile);
    }
    catch (ParseError const& ex) {
        std::cout << "ParseError: " << ex.what() << std::endl;
    }

    delete parse;
    return 0;
}
