#ifndef PARSER_HH
#define PARSER_HH

#include <string>

template <typename>
inline constexpr bool c_alwaysFalse = false;

namespace Parser {
    namespace Helper {
        int parseInt(std::string& text);
        float parseFloat(std::string& text);
    }

    /*
     * @brief parse number in words to numbers
     *        only takes words that are numbers
     * @param string that only consists of number i.e. (one, two, ...)
     * @return int or float according to template T
     */
    template <typename T>
    T parseNumber(std::string text) {
        if constexpr (std::is_same_v<T, int>) {
            return Helper::parseInt(text);
        } else if constexpr (std::is_same_v<T, float>) {
            return Helper::parseFloat(text);
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

};

#endif // PARSER_HH
