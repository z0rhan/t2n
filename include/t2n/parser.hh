#ifndef PARSER_HH
#define PARSER_HH

#include "error.hh"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>

const std::unordered_map<std::string, int> s_UNITS = {
    {"zero", 0},     {"one", 1},        {"two", 2},       {"three", 3},
    {"four", 4},     {"five", 5},       {"six", 6},       {"seven", 7},
    {"eight", 8},    {"nine", 9},       {"ten", 10},      {"eleven", 11},
    {"twelve", 12},  {"thirteen", 13},  {"fourteen", 14}, {"fifteen", 15},
    {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19}};

const std::unordered_map<std::string, int> s_TENS = {
    {"twenty", 20}, {"thirty", 30},  {"forty", 40},  {"fifty", 50},
    {"sixty", 60},  {"seventy", 70}, {"eighty", 80}, {"ninety", 90}};

const std::unordered_map<std::string, int> s_SCALES = {
    {"hundred", 100}, {"thousand", 1000},
    {"million", 1000000}, {"billion", 1000000000}};

template <typename>
inline constexpr bool c_alwaysFalse = false;

class Parser {
public:
    Parser() = default;
    ~Parser() = default;

    /*
     * @brief parse number in words to numbers
     *        only takes words that are numbers
     * @param string that only consists of number i.e. (one, two, ...)
     * @return int or float according to template T
     */
    template <typename T>
    T parseNumber(std::string text) {
        if constexpr (std::is_same_v<T, int>) {
            return parseInt(text);
        } else if constexpr (std::is_same_v<T, float>) {
            return parseFloat(text);
        } else {
            static_assert(c_alwaysFalse<T>, "Type not supported");
        }
    }

    /*
     * @brief parse number in words from any string to numbers
     * @param any arbitary string
     * @return string whose numbers in words are converted to numbers
     */
    std::string parse(std::string& text, const bool isFloat = false);

    /*
     * @brief Read from a file and parses the text content line by line
     *        Writes to a file 'output.txt' the result
     * @param filename
     */
    void parseFile(const std::string& fileName);

private:
    static int parseInt(std::string& text);
    static float parseFloat(std::string& text);
    static std::string parseText(std::string &text, const bool isFloat = false);

    static std::vector<std::string> tokenize(const std::string& text);
    static std::string handleTokens(const std::vector<std::string>& tokens,
                                    const bool isFloat = false);
    static double convertToNum(const std::vector<std::string>& tokens);
    static bool handleDecimals(const std::vector<std::string>& tokens,
                                      size_t& index, std::ostringstream& result);
};

#endif // PARSER_HH
