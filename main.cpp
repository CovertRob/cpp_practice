// Write a program that asks the user to enter their full name and their age. As output, tell the user the sum of their age and the number of characters in their name (use the std::string::length() member function to get the length of the string). For simplicity, count any spaces in the name as a character.

// Sample output:

// Enter your full name: John Doe
// Enter your age: 32
// Your age + length of name is: 40

// #include <iostream>
// #include <string>

// int main(int argc, char const *argv[])
// {
//     /* code */
//     std::cout << "Enter your full name: ";
//     std::string fullName{};
//     std::getline(std::cin >> std::ws, fullName);
//     std::cout << "Enter your age: ";
//     int age{};
//     std::cin >> age;
//     using namespace std::string_literals;
//     int name_and_age {age + static_cast<int>(fullName.length())};
//     std::cout << "Your age + length of name is: " << name_and_age;
//     return 0;
// }

// Write a program that asks the user to input an integer, and tells the user whether the number is even or odd. Write a constexpr function called isEven() that returns true if an integer passed to it is even, and false otherwise. Use the remainder operator to test whether the integer parameter is even. Make sure isEven() works with both positive and negative numbers.

// Show Hint

// Your program should match the following output:

// Enter an integer: 5
// 5 is odd

// #include <iostream>

// constexpr bool isEven(int num) 
// {
//     return (num % 2) == 0;
// }

// int main(int argc, char const *argv[])
// {
    
//     std::cout << "Enter an integer: ";
//     int input {};
//     std::cin >> input;
//     bool evaluation = isEven(input);
//     if (evaluation)
//         std::cout << input << " is even" << "\n";
//     else
//         std::cout << input << " is odd" << "\n";
//     return 0;
// }


// Write a program that asks the user to enter two integers, one named smaller, the other named larger. If the user enters a smaller value for the second integer, use a block and a temporary variable to swap the smaller and larger values. Then print the values of the smaller and larger variables. Add comments to your code indicating where each variable dies. Note: When you print the values, smaller should hold the smaller input and larger the larger input, no matter which order they were entered in.

// The program output should match the following:

// Enter an integer: 4
// Enter a larger integer: 2
// Swapping the values
// The smaller value is 2
// The larger value is 4

// #include <iostream>

// int main()
// {
//     std::cout << "Enter an integer: ";
//     int smaller{};
//     std::cin >> smaller;

//     std::cout << "Enter a larger integer: ";
//     int larger{};
//     std::cin >> larger;

//     // if user did it wrong
//     if (smaller > larger)
//     {
//         // swap values of smaller and larger
//         std::cout << "Swapping the values\n";

//         int temp{ larger };
//         larger = smaller;
//         smaller = temp;
//     } // temp dies here

//     std::cout << "The smaller value is: " << smaller << '\n';
//     std::cout << "The larger value is: " << larger << '\n';

//     return 0;
// } // smaller and larger die here

// Fix the following program

// #include <iostream>

// int main()
// {
// 	std::cout << "Enter a positive number: ";
// 	int num{};
// 	std::cin >> num;


// 	if (num < 0) {
// 		std::cout << "Negative number entered.  Making positive.\n";
// 		num = -num;
//     } // Must use block to have second line flow properly
// 	std::cout << "You entered: " << num;

// 	return 0;
// }

// Write a file named constants.h that makes the following program run. If your compiler is C++17 capable, use an inline constexpr variable. Otherwise, use a normal constexpr variable. maxClassSize should have value 35.

// main.cpp:

// #include "constants.h"
// #include <iostream>

// int main()
// {
// 	std::cout << "How many students are in your class? ";
// 	int students{};
// 	std::cin >> students;


// 	if (students > Constants::maxClassSize)
// 		std::cout << "There are too many students in this class";
// 	else
// 		std::cout << "This class isn't too large";

// 	return 0;
// }


// File:
// #ifndef CONSTANTS_H
// #define CONSTANTS_H

// namespace Constants
// {
//     inline constexpr int maxClassSize {15};  
// } 

// #endif

// Write a function int accumulate(int x). This function should return the sum of all of the values of x that have been passed to this function.

// The following program should run and produce the output noted in comments:

// #include <iostream>

// int accumulate(int var) 
// {
//     static int sum{0};
//     return sum+= var;
// }

// int main()
// {
//     std::cout << accumulate(4) << '\n'; // prints 4
//     std::cout << accumulate(3) << '\n'; // prints 7
//     std::cout << accumulate(2) << '\n'; // prints 9
//     std::cout << accumulate(1) << '\n'; // prints 10

//     return 0;
// }

