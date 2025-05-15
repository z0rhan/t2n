#include "parser.hh"
#include "error.hh"
#include <string>

constexpr static char s_DELIMITER = ' ';
const static std::string s_OUTPUT_FILE = "output.txt";

//------------------------------------------------------------------------------
// PUBLIC INTERFACE
void Parser::parseFile(const std::string& fileName) {
    std::ifstream inputFileObj(fileName);
    std::ofstream outputFileObj(s_OUTPUT_FILE);
    
    if (!inputFileObj) {
        throw ParseError("Error in reading file!!!");
    }

    if (!outputFileObj) {
        throw ParseError("Error writing to file!!!");
    }

    std::string line;
    while(std::getline(inputFileObj, line)) {
        std::string result = parse<std::string>(line);
        outputFileObj << result << "\n";
    }

    inputFileObj.close();
    outputFileObj.close();
}


//------------------------------------------------------------------------------
// PRIVATE INTERFACE

std::string Parser::parseText(std::string& text) {
    std::vector<std::string> tokens = tokenize(text);
       
    std::string output = handleTokens(tokens);

    return output;
}

std::vector<std::string> Parser::tokenize(const std::string& text) {
    std::vector<std::string> tokens; 
    std::string temp;

    for (char c : text) {
        if (c == s_DELIMITER) {
            tokens.push_back(temp);
            temp.clear();

            continue;
        }

        temp += c;
    }

    if (!temp.empty()) {
        tokens.push_back(temp);
    }

    return tokens;
}

std::string Parser::handleTokens(const std::vector<std::string>& tokens) {
    std::ostringstream result;
    std::vector<std::string> numberBlock;

    for (size_t i = 0; i < tokens.size(); i++) {
        std::string token = tokens[i];
        std::string tokenLowercase = token;
        std::transform(tokenLowercase.begin(),
                       tokenLowercase.end(),
                       tokenLowercase.begin(),
                       [](char c) {return std::tolower(c);});

        if (s_UNITS.count(tokenLowercase) ||
            s_TENS.count(tokenLowercase) ||
            s_SCALES.count(tokenLowercase))
        {
            numberBlock.push_back(tokenLowercase);

            continue;
        }

        if (!numberBlock.empty()) {
            double num = convertToNum(numberBlock);

            result << num << " ";
            numberBlock.clear();
        }
        
        result << token;

        if (i != tokens.size() - 1) {
            result << " ";
        }
    }

    if (!numberBlock.empty()) {
        double num = convertToNum(numberBlock);

        result << num;
    }
    
    return result.str();
}

double Parser::convertToNum(const std::vector<std::string>& tokens) {
    double current = 0.00;
    double result = 0.00;

    for (const std::string& token : tokens) {
        if (s_UNITS.count(token)) {
            current += s_UNITS.at(token);
        } else if (s_TENS.count(token)) {
            current += s_TENS.at(token);
        } else if (token == "hundred") {
            current *= 100; // Exception for hundred => hundred million
        } else if (s_SCALES.count(token)) {
            current *= s_SCALES.at(token);
            result += current;
            current = 0.00;
        }

    }

    return result + current;
}
