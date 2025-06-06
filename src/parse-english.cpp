#include "parse-english.hh"

#include <sstream>
#include <algorithm>

const static std::string s_POINT = "point";

//------------------------------------------------------------------------------
double convertToNum(const std::vector<std::string> &tokens);
bool handleDecimals(const std::vector<std::string> &tokens, size_t &index,
                    std::ostringstream &result);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public
std::string English::handleTokens(const std::vector<std::string> &tokens, const bool isFloat)
{
    std::ostringstream result;
    std::vector<std::string> numberBlock;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::string token = tokens[i];
        std::string tokenLowercase = token;
        std::transform(tokenLowercase.begin(), tokenLowercase.end(), tokenLowercase.begin(),
                       [](char c) { return std::tolower(c); });

        if (s_UNITS.count(tokenLowercase) || s_TENS.count(tokenLowercase) ||
            s_SCALES.count(tokenLowercase))
        {
            numberBlock.push_back(tokenLowercase); // gather the numbers

            continue;
        }

        if (isFloat && tokenLowercase == s_POINT && !numberBlock.empty())
        {
            double num = convertToNum(numberBlock);
            result << num;
            numberBlock.clear();
            if (handleDecimals(tokens, i, result))
            {
                continue;
            }
        }

        if (!numberBlock.empty())
        {
            double num = convertToNum(numberBlock);

            result << num << " ";
            numberBlock.clear();
        }

        result << token;

        if (i != tokens.size() - 1)
        {
            result << " ";
        }
    }

    if (!numberBlock.empty())
    {
        double num = convertToNum(numberBlock);

        result << num;
    }

    return result.str();
}

//------------------------------------------------------------------------------
// Private
double convertToNum(const std::vector<std::string> &tokens)
{
    double current = 0.00;
    double result = 0.00;

    for (const std::string &token : tokens)
    {
        if (s_UNITS.count(token))
        {
            current += s_UNITS.at(token);
        }
        else if (s_TENS.count(token))
        {
            current += s_TENS.at(token);
        }
        else if (token == "hundred")
        {
            current *= 100; // Exception for hundred => hundred million
        }
        else if (s_SCALES.count(token))
        {
            current *= s_SCALES.at(token);
            result += current;
            current = 0.00;
        }
    }

    return result + current;
}

bool handleDecimals(const std::vector<std::string> &tokens, size_t &index,
                    std::ostringstream &result)
{
    bool isValidFloat = false;
    index++;

    while (index < tokens.size())
    {
        std::string token = tokens[index];
        std::string tokenLowercase = token;
        std::transform(tokenLowercase.begin(), tokenLowercase.end(), tokenLowercase.begin(),
                       [](char c) { return std::tolower(c); });

        if (s_UNITS.count(tokenLowercase))
        {
            if (!isValidFloat)
            {
                result << ".";
            }

            isValidFloat = true;
            result << s_UNITS.at(tokenLowercase);
            index++;

            continue;
        }

        result << " " << token << " ";
        return isValidFloat; // If no more numbers
    }

    index--;
    return isValidFloat;
}
