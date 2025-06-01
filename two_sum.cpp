// Write a function that takes an array of numbers (integers for the tests) and a target number. It should find two different items in the array that, when added together, give the target value. The indices of these items should then be returned in a tuple / list (depending on your language) like so: (index1, index2).

// For the purposes of this kata, some tests may have multiple answers; any valid solutions will be accepted.

// The input will always be valid (numbers will be an array of length 2 or greater, and all of the items will be numbers; target will always be the sum of two different items from that array).

// Based on: https://leetcode.com/problems/two-sum/

// two_sum({1, 2, 3}, 4); // returns {0, 2} or {2, 0}
// two_sum({3, 2, 4}, 6); // returns {1, 2} or {2, 1}

// Edge cases to consider:

// Loop logic potential out of bounds when looping to numbers.size() and doing an i+1 access

// When using a sorted vector for O(n) access need to consider duplicate indices for repeating elements

// Must check all pairs by using two pointer method

#include <utility>
#include <vector>
#include <algorithm>

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int>& numbers, int target) {

    std::vector<int> num_copy = numbers; // Make copy for sorting
    std::sort(num_copy.begin(), num_copy.end()); // Sort copy for O(n) access

    int left {0}; // Begin index
    int right {static_cast<int>(num_copy.size()-1)}; // End index

    int a {0};
    int b {0};

    while (left < right) {
        int sum = num_copy[left] + num_copy[right];
        if (sum == target) {
            a = num_copy[left];
            b = num_copy[right];
            break;
        }
        else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }
    // map a and b back to their original indices
    std::size_t index1 = std::find(numbers.begin(), numbers.end(), a) - numbers.begin();
    std::size_t index2 = std::find(numbers.begin(), numbers.end(), b) - numbers.begin();

    // Make sure indices are distinct (important for duplicate values like 5 + 5 = 10)
    if (index1 == index2) {
        index2 = std::find(numbers.begin() + index1 + 1, numbers.end(), b) - numbers.begin();
    }

    return {index1, index2};    
}

// Example using a hash map:

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int>& numbers, int target) {
    std::unordered_map<int, std::size_t> seen;

    for (std::size_t i = 0; i < numbers.size(); ++i) {
        int complement = target - numbers[i];

        // Have we seen the complement before?
        auto it = seen.find(complement);
        if (it != seen.end()) {
            return {it->second, i};
        }

        // Store current number and its index
        seen[numbers[i]] = i;
    }

    return {0, 0}; // or throw an exception if no valid pair is guaranteed
}