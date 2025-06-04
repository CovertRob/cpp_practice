// Given two arrays of strings a1 and a2 return a sorted array r in lexicographical order of the strings of a1 which are substrings of strings of a2.

// Example 1:
// a1 = ["arp", "live", "strong"]

// a2 = ["lively", "alive", "harp", "sharp", "armstrong"]

// returns ["arp", "live", "strong"]

// Example 2:
// a1 = ["tarp", "mice", "bull"]

// a2 = ["lively", "alive", "harp", "sharp", "armstrong"]

// returns []

// Notes:
// Arrays are written in "general" notation. See "Your Test Cases" for examples in your language.
// In Shell bash a1 and a2 are strings. The return is a string where words are separated by commas.
// Beware: In some languages r must be without duplicates.

// Do not include duplicates for C++ seen from test examples
#include <vector>
#include <string>
#include <algorithm>

class WhichAreIn
{

  public:
  static std::vector<std::string> inArray(std::vector<std::string> &array1, std::vector<std::string> &array2)
  {
    std::vector<std::string> substr_match;

    for (auto &&i : array1) {
        for (auto &&j : array2) {
            if (j.find(i) != std::string::npos)
            {
                substr_match.push_back(i);
                break;
            }
            
        }
    }
    std::sort(substr_match.begin(), substr_match.end());
    return substr_match;
  };
};
