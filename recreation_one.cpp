// 1, 246, 2, 123, 3, 82, 6, 41 are the divisors of number 246.

// Squaring these divisors we get: 1, 60516, 4, 15129, 9, 6724, 36, 1681.

// The sum of these squares is 84100 which is 290 * 290.

// Task
// Find all integers between m and n (m and n are integers with 1 <= m <= n) such that the sum of their squared divisors is itself a square.

// We will return an array of subarrays or of tuples (in C an array of Pair) or a string.

// The subarrays (or tuples or Pairs) will have two elements: first the number the squared divisors of which is a square and then the sum of the squared divisors.

// Example:
// m =  1, n = 250 --> [[1, 1], [42, 2500], [246, 84100]]
// m = 42, n = 250 --> [[42, 2500], [246, 84100]]
// The form of the examples may change according to the language, see "Sample Tests".

/*
Problem:
    I am given two inputs, m and n. I need to find the divisors for all of the integers in that range. I need to then square all those divisors and sum them up. Then, if that sum is a perfect square, add that to my result. 

Examples: 
    m =  1, n = 250 --> [[1, 1], [42, 2500], [246, 84100]]
    m = 42, n = 250 --> [[42, 2500], [246, 84100]]

    I see in the examples that the results are in a nested array (vector) and are in pair format. The first number is the base integer and the second number is the sum of it's divisors that is a perfect square

Data Structures:
    Based on the provided skeleton, I will need to return a vector that contains pairs. Internally, I will need to use a vector to store the computed divisors. 

Algorithm:  

    Initialize vector of pairs to hold return value
    SET for loop for range from m to in, inclusive
        SET vector to hold divisors of current index
        calculate all divisors of current index
        calculate the sum of squaring all the divisors for current index
        IF the square root of the sum is a perfect square, add it to the return vector as a pair with the index.  
*/

// #include <utility>
// #include <vector>
// #include <cmath>
// #include <iostream>

// class SumSquaredDivisors
// {
// public:
//     static std::vector<std::pair<long long, long long>> listSquared(long long m, long long n) {
//     std::vector<std::pair<long long, long long>> output;
//     // Range from m to n, inclusive
//     for (int i = m; i <= n; ++i)
//     {
//         std::vector<long long> divisors;
//         // Only iterate up to the squareroot
//         for (int divisor = 1; divisor <= sqrt(i); ++divisor)
//         {
//             double div_value = static_cast<double>(i) / static_cast<double>(divisor);
//             if ((i % divisor) == 0.0)
//             {
//                 divisors.push_back(divisor);
//                 if (divisor != (i / divisor)) {
//                     divisors.push_back(i / divisor);
//                 }
//             }            
//         }
//         // Calculate the sum of squares
//         long long sum { ([divisors](){
//             long long result{};
//             for (auto &&i : divisors)
//             {
//                 result += (i * i);
//             }
//             return result;
//          })() };

//          // If the floor division of the square root of the sum is a perfect square, add it to the output
//          long long root {static_cast<long long>(sqrt(sum))};
//          if (root * root == sum) {
//             output.push_back({i, sum});
//          }
//     }
//     return output;
// }
// };

// Original solution: above avoids most float point math

#include <utility>
#include <vector>
#include <cmath>
#include <iostream>

class SumSquaredDivisors
{
public:
    static std::vector<std::pair<long long, long long>> listSquared(long long m, long long n) {
    std::vector<std::pair<long long, long long>> output;
    // Range from m to n, inclusive
    for (int i = m; i <= n; ++i)
    {
        std::vector<long long> divisors;
        // Only iterate up to the squareroot
        for (int divisor = 1; divisor <= sqrt(i); ++divisor)
        {
            double div_value = static_cast<double>(i) / static_cast<double>(divisor);
            if (std::fmod(div_value, 1.0) == 0.0)
            {
                // Avoid duplicate for perfect square
                if (divisor != div_value) {
                    divisors.push_back(divisor);
                    divisors.push_back(div_value);
                }
                else {
                    divisors.push_back(divisor);
                }
            }            
        }
        // Calculate the sum of squares
        long long sum { ([divisors](){
            long long result{};
            for (auto &&i : divisors)
            {
                result += (i * i);
            }
            return result;
         })() };

         // If the floor division of the square root of the sum is a perfect square, add it to the output
         if (std::fmod(sqrt(sum), 1.0) == 0.0) {
            output.push_back({i, sum});
         }
    }
    return output;
}
};

int main(int argc, char const *argv[])
{
    auto result = SumSquaredDivisors::listSquared(1, 250);
    for (auto &&i : result)
    {
        std::cout << "(" << i.first << ", " << i.second << ")\n";
    }
    
    return 0;
}
