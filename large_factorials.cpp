// In mathematics, the factorial of integer n is written as n!. It is equal to the product of n and every integer preceding it. For example: 5! = 1 x 2 x 3 x 4 x 5 = 120

// Your mission is simple: write a function that takes an integer n and returns the value of n!.

// You are guaranteed an integer argument. For any values outside the non-negative range, return null, nil or None (return an empty string "" in C and C++). For non-negative numbers a full length number is expected for example, return 25! =  "15511210043330985984000000"  as a string.

// For more on factorials, see http://en.wikipedia.org/wiki/Factorial

// NOTES:

// The use of BigInteger or BigNumber functions has been disabled, this requires a complex solution

// I have removed the use of require in the javascript language.

/*
Problem: Need to create a function that returns the factorial of a given positive integer in string format. 

    Input: integer which is the base factorial
    Output: string representing the full factorial computed

Examples:
    25! =  "15511210043330985984000000"
    This is 1 x 2 x 3 x 4 x 5 ... all the way up to 25 inclusive

Data Structures: 
    strings
    integers
    perhaps chars for manipulating individual places in string

Algorithm: 

    Utilizing a range, multiply starting at 1 up to the range value

*/

#include <vector>
#include <string>

std::string factorial(int factorial) {
    // Instantiate vector to hold numbers
   std::vector<int> result{1};
    // loop until i is the factorial number
   for (int i = 2; i <= factorial; ++i) {
        int carry = 0;
        // for each i, we must multiply each number space by the current i value long hand multiplication wise and handle carry values as needed
        for (size_t j = 0; j < result.size(); ++j) {
            int prod = result[j] * i + carry;
            result[j] = prod % 10; // Keep the ones digit
            carry = prod / 10; // Carry the remaining digits
        }
        // This will only execute if there is a left over carry value after multiplying all places above. Therefore, this will only execute at the end to add on the carry to the front of the number, just like in long hand multiplication
        while (carry > 0) {
            result.push_back(carry % 10); // Add lowest digit of carry
            carry /= 10; // Remove that digit
        }
   }
   // In reverse order, create a string out of the result
   std::string str;
   for (auto it = result.rbegin(); it != result.rend(); ++it) {
    str += std::to_string(*it);
   }
   return str;
}
