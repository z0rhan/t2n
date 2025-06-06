#pragma once

#include <string>
#include <unordered_map>
#include <vector>

const std::unordered_map<std::string, int> s_UNITS = {
    {"zero", 0},     {"one", 1},      {"two", 2},        {"three", 3},     {"four", 4},
    {"five", 5},     {"six", 6},      {"seven", 7},      {"eight", 8},     {"nine", 9},
    {"ten", 10},     {"eleven", 11},  {"twelve", 12},    {"thirteen", 13}, {"fourteen", 14},
    {"fifteen", 15}, {"sixteen", 16}, {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19}};

const std::unordered_map<std::string, int> s_TENS = {
    {"twenty", 20}, {"thirty", 30},  {"forty", 40},  {"fifty", 50},
    {"sixty", 60},  {"seventy", 70}, {"eighty", 80}, {"ninety", 90}};

const std::unordered_map<std::string, int> s_SCALES = {
    {"hundred", 100}, {"thousand", 1000}, {"million", 1000000}, {"billion", 1000000000}};

namespace English
{
std::string handleTokens(const std::vector<std::string> &tokens, const bool isFloat);

}
