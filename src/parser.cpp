#include "parser.hh"
#include "error.hh"
#include "parse-english.hh"

#include <stdexcept>
#include <string>
#include <fstream>

constexpr static char s_DELIMITER = ' ';
const static std::string s_OUTPUT_FILE = "output.txt";
const static std::string s_POINT = "point";

//------------------------------------------------------------------------------
int Parser::Helper::parseInt(std::string &text);
std::string parseText(std::string &text, const bool isFloat = false);
std::vector<std::string> tokenize(const std::string &text);
// Note this maxPerLine can be exceeded by a lenght of word
void writeToFile(const std::string& text, const size_t& maxPerLine, std::ofstream& fileObj);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PUBLIC INTERFACE
void Parser::parseFile(const std::string &fileName)
{
    std::vector<std::string> tokens;

    std::ifstream inputFileObj(fileName);
    if (!inputFileObj)
    {
        throw ParseError("Error in reading file!!!");
    }

    std::string line;
    while (std::getline(inputFileObj, line))
    {
        std::vector<std::string> currentTokens = tokenize(line);
        tokens.insert(tokens.end(), currentTokens.begin(), currentTokens.end());
    }
    inputFileObj.close();

    std::ofstream outputFileObj(s_OUTPUT_FILE);
    if (!outputFileObj)
    {
        throw ParseError("Error writing to file!!!");
    }

    std::string result = English::handleTokens(tokens, true);
    writeToFile(result, 80, outputFileObj); // write with approx 80 char per line
    outputFileObj.close();
}

//------------------------------------------------------------------------------
// PRIVATE INTERFACE
int Parser::Helper::parseInt(std::string &text)
{
    try
    {
        return std::stoi(parseText(text));
    }
    catch (std::invalid_argument const &e)
    {
        throw ParseError(e.what());
    }
}

float Parser::Helper::parseFloat(std::string &text)
{
    try
    {
        return std::stof(parseText(text, true));
    }
    catch (std::invalid_argument const &e)
    {
        throw ParseError(e.what());
    }
}

std::string parseText(std::string &text, const bool isFloat)
{
    std::vector<std::string> tokens = tokenize(text);

    std::string output = English::handleTokens(tokens, isFloat);

    return output;
}

std::vector<std::string> tokenize(const std::string &text)
{
    std::vector<std::string> tokens;
    std::string temp;

    for (char c : text)
    {
        if (c == s_DELIMITER)
        {
            tokens.push_back(temp);
            temp.clear();

            continue;
        }

        temp += c;
    }

    if (!temp.empty())
    {
        tokens.push_back(temp);
    }

    return tokens;
}

void writeToFile(const std::string& text, const size_t& maxPerLine, std::ofstream& fileObj)
{
    size_t lineLength = 0;

    for (size_t i = 0; i < text.size(); ++i)
    {
        char c = text[i];

        if (lineLength > maxPerLine && c == ' ')
        {
            fileObj.put('\n');
            lineLength = 0;
        }

        fileObj.put(c);
        lineLength++;
    }
}
