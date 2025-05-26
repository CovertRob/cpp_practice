# Important Tidbits from learncpp.com

## Header Files
- For gcc, you can use the -I option to specify an alternate include directory: `g++ -o main -I./source/includes main.cpp`
- There is no space after the -I. For a full path (rather than a relative one), remove the . after -I

- For VS Code: In your tasks.json configuration file, add a new line in the “Args” section: `-I./source/includes`

- To maximize the chance that missing includes will be flagged by the compiler, order by the folloiwng:
    - The paired header file for this code file (e.g. add.cpp should #include "add.h")
    - Other headers from the same project (e.g. #include "mymath.h")
    - 3rd party library headers (e.g. #include <boost/tuple/tuple.hpp>)
    - Standard library headers (e.g. #include <iostream>)
- Can use `#pragma once` instead of normal header guard `#ifndef #define and #endif`

## Debugging

- Use std::cerr when printing debug statements sincce std::cout is buffered and may not output correct if the program crashes
- Recommended to use loggers like `<plog/Log.h>`
- Example:

~~~C++
#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput()
{
	PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library

	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger

	PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console

	int x{ getUserInput() };
	std::cout << "You entered: " << x << '\n';

	return 0;
}
~~~

## Integers

- Arithmetic overflow (when an integer size can't hold the number) results in undefined behavior
- By default integer division is done between two integers and the fraction portion is dropped, NOT rounded
- If you overflow on an unsigned int by trying to assign a number outside the 255 in 8 bits it will wrap around like modulo
- Avoid comparing signed and unsigned ints, it will convert to unsigned and give crazy answers
- int size is not guaranteed to be 16 or 32, changes from system to system
- Fixed width integers were introduced in C++11 to fix the above
- The fixed-width integers actually don’t define new types -- they are just aliases for existing integral types with the desired size. For each fixed-width type, the implementation (the compiler and standard library) gets to determine which existing type is aliased. As an example, on a platform where int is 32-bits, std::int32_t will be an alias for int. On a system where int is 16-bits (and long is 32-bits), std::int32_t will be an alias for long instead.

### Integer Best Practice

Prefer int when the size of the integer doesn’t matter (e.g. the number will always fit within the range of a 2-byte signed integer). For example, if you’re asking the user to enter their age, or counting from 1 to 10, it doesn’t matter whether int is 16-bits or 32-bits (the numbers will fit either way). This will cover the vast majority of the cases you’re likely to run across.
Prefer std::int#_t when storing a quantity that needs a guaranteed range.
Prefer std::uint#_t when doing bit manipulation or well-defined wrap-around behavior is required (e.g. for cryptography or random number generation).
Avoid the following when possible:

short and long integers (prefer a fixed-width integer type instead).
The fast and least integral types (prefer a fixed-width integer type instead).
Unsigned types for holding quantities (prefer a signed integer type instead).
The 8-bit fixed-width integer types (prefer a 16-bit fixed-width integer type instead).
Any compiler-specific fixed-width integers (for example, Visual Studio defines __int8, __int16, etc…)

- std::size_t is an alias for an implementation-defined unsigned integral type. It is used within the standard library to represent the byte-size or length of objects.

## Floats

- Comparing floats due to rounding inaccuraccies can be problematic
- Rounding errors occur when a number can’t be stored precisely. This can happen even with simple numbers, like 0.1. Therefore, rounding errors can, and do, happen all the time. Rounding errors aren’t the exception -- they’re the norm. Never assume your floating point numbers are exact.
	- A corollary of this rule is: be wary of using floating point numbers for financial or currency data.

## Type Conversion

- Implicit and explicit type conversions - prefer explicity when needed, the compiler should warn about implicit
- Implicit can occur when creating a new variable, passing as parameter to function, and at the point of return in a function
~~~C++
#include <iostream>

int getInt(int c)
{
	return c;
}

int main()
{
	std::cout << "Enter a single character: ";
	char c{};
	std::cin >> c;

	std::cout << "You entered '" << c << "', which has ASCII code " << getInt(c) << ".\n";

	return 0;
}
~~~

## Constant expressions

- Compile-time constant	A value or non-modifiable object whose value must be known at compile time (e.g. literals and constexpr variables).
- Constexpr	Keyword that declares objects as compile-time constants (and functions that can be evaluated at compile-time). Informally, shorthand for “constant expression”.
- Constant expression	An expression that contains only compile-time constants and operators/functions that support compile-time evaluation.
- Runtime expression	An expression that is not a constant expression.
- Runtime constant	A value or non-modifiable object that is not a compile-time constant.

## String and string_view
- " " are C-style string literals, not fundamental types
- Must use `std::string` which are objects, to get dynamic string types
- Preferred to  use std::string_view which provides for read-only access to avoid excessive initializing and copying
- Can access using suffixes as well
~~~C++
using namespace std::string_literals;      // access the s suffix
using namespace std::string_view_literals; // access the sv suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal
~~~
- string_view's are preferred for `constexpr` over `string`
- A view is dependent on the object being viewed. If the object being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result.
- Do not initialize a std::string_view with a std::string literal, as this will leave the std::string_view dangling.
- It is okay to initialize a std::string_view with a C-style string literal or a std::string_view literal. It’s also okay to initialize a std::string_view with a C-style string object, a std::string object, or a std::string_view object, as long as that string object outlives the view.

## Operator Precedence

| Prec/Ass | Operator | Description | Pattern |
|:--------:|:--------:|:------------|:--------|
| 1 L->R | `::` | Global scope (unary), Namespace scope (binary) | `::name`, `class_name::member_name` |
| 2 L->R | `() [] . -> ++ -- typeid const_cast dynamic_cast reinterpret_cast static_cast sizeof… noexcept alignof` | Parentheses, Function call, Functional cast, List init (C++11), Array subscript, Member access, Post-increment, Post-decrement, RTTI, Casts, sizeof, noexcept, alignof | `(expression)`, `function_name(arguments)`, `type(expression)`, `type{expression}`, `pointer[expression]`, `object.member_name`, `object_pointer->member_name`, `lvalue++`, `lvalue--`, `typeid(type)`, `const_cast<type>(expression)`, `dynamic_cast<type>(expression)`, `reinterpret_cast<type>(expression)`, `static_cast<type>(expression)`, `sizeof...(expression)`, `noexcept(expression)`, `alignof(type)` |
| 3 R->L | `+ - ++ -- ! not ~ (type) sizeof co_await & * new new[] delete delete[]` | Unary operations: plus, minus, pre-increment, pre-decrement, logical NOT, bitwise NOT, C-style cast, sizeof, co_await (C++20), address-of, dereference, new/delete | `+expression`, `-expression`, `++lvalue`, `--lvalue`, `!expression`, `not expression`, `~expression`, `(new_type)expression`, `sizeof(type)`, `co_await expression`, `&lvalue`, `*expression`, `new type`, `new type[expression]`, `delete pointer`, `delete[] pointer` |
| 4 L->R | `->* .*` | Member pointer selector, Member object selector | `object_pointer->*pointer_to_member`, `object.*pointer_to_member` |
| 5 L->R | `* / %` | Multiplication, Division, Remainder | `expression * expression`, `expression / expression`, `expression % expression` |
| 6 L->R | `+ -` | Addition, Subtraction | `expression + expression`, `expression - expression` |
| 7 L->R | `<< >>` | Bitwise shift left/right, Insertion/Extraction | `expression << expression`, `expression >> expression` |
| 8 L->R | `<=>` | Three-way comparison (C++20) | `expression <=> expression` |
| 9 L->R | `< <= > >=` | Comparison operators | `expression < expression`, `expression <= expression`, `expression > expression`, `expression >= expression` |
| 10 L->R | `== !=` | Equality, Inequality | `expression == expression`, `expression != expression` |
| 11 L->R | `&` | Bitwise AND | `expression & expression` |
| 12 L->R | `^` | Bitwise XOR | `expression ^ expression` |
| 13 L->R | `|` | Bitwise OR | `expression | expression` |
| 14 L->R | `&& and` | Logical AND | `expression && expression`, `expression and expression` |
| 15 L->R | `|| or` | Logical OR | `expression || expression`, `expression or expression` |
| 16 R->L | `throw co_yield ?: = *= /= %= += -= <<= >>= &= |= ^=` | Throw, Yield (C++20), Conditional, Assignments | `throw expression`, `co_yield expression`, `expression ? expression : expression`, `lvalue = expression`, `lvalue *= expression`, `lvalue /= expression`, `lvalue %= expression`, `lvalue += expression`, `lvalue -= expression`, `lvalue <<= expression`, `lvalue >>= expression`, `lvalue &= expression`, `lvalue |= expression`, `lvalue ^= expression` |
| 17 L->R | `,` | Comma operator | `expression, expression` |

- **GCC evaluates parameters passed to functions from right to left order**
- Clang compiler evaluates left to right
- The above can mess up assignemt of positional arguments to function calls if not careful

## Arithmetic Operations

- When doing a remainder comparison, compare against 0 (like when checking if a number of odd or even) because remainder can be positive or negative
- Note that C++ `%` operator does not behave like a true mathematical modulo operation, best to refer to as remainder
- The `^` operator is bitwise not regular exponentiation, you have to write your own function
- You can use `pow()` from `cmath` but it returns a double type and not int
~~~C++
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>
#include <limits> // for std::numeric_limits

// A safer (but slower) version of powint() that checks for overflow
// note: exp must be non-negative
// Returns std::numeric_limits<std::int64_t>::max() if overflow occurs
constexpr std::int64_t powint_safe(std::int64_t base, int exp)
{
    assert(exp >= 0 && "powint_safe: exp parameter has negative value");

    // Handle 0 case
    if (base == 0)
        return (exp == 0) ? 1 : 0;

    std::int64_t result { 1 };

    // To make the range checks easier, we'll ensure base is positive
    // We'll flip the result at the end if needed
    bool negativeResult{ false };

    if (base < 0)
    {
        base = -base;
        negativeResult = (exp & 1);
    }

    while (exp > 0)
    {
        if (exp & 1) // if exp is odd
        {
            // Check if result will overflow when multiplied by base
            if (result > std::numeric_limits<std::int64_t>::max() / base)
            {
                std::cerr << "powint_safe(): result overflowed\n";
                return std::numeric_limits<std::int64_t>::max();
            }

            result *= base;
        }

        exp /= 2;

        // If we're done, get out here
        if (exp <= 0)
            break;

        // The following only needs to execute if we're going to iterate again

        // Check if base will overflow when multiplied by base
        if (base > std::numeric_limits<std::int64_t>::max() / base)
        {
            std::cerr << "powint_safe(): base overflowed\n";
            return std::numeric_limits<std::int64_t>::max();
        }

        base *= base;
    }

    if (negativeResult)
        return -result;

    return result;
}

int main()
{
	std::cout << powint_safe(7, 12) << '\n'; // 7 to the 12th power
	std::cout << powint_safe(70, 12) << '\n'; // 70 to the 12th power (will return the max 64-bit int value)

	return 0;
}
~~~
- Important to differentiate post-fix and pre-fix arithmetic operations

| Type | Description |
|:--------:|:--------:|
| Prefix increment (pre-increment)	++	++x	| Increment x, then return x |
| Prefix decrement (pre-decrement)	––	––x	| Decrement x, then return x |
| Postfix increment (post-increment)	++	x++	| Copy x, then increment x, then return the copy |
| Postfix decrement (post-decrement)	––	x–– | Copy x, then decrement x, then return the copy |

- The postfix increment/decrement operators are trickier. First, a copy of the operand is made. Then the operand (not the copy) is incremented or decremented. Finally, the copy (not the original) is evaluated. 
- C++ does not define the order of function argument evaluation so using operators with side-effects can cause undefined behavior
- The comma operator evaluates the left operand, then the right operand, and then returns the result of the right operand. General notion is to not use this one...

## Variable Shadowing

- GCC and Clang support the flag -Wshadow that will generate warnings if a variable is shadowed. There are several subvariants of this flag `-Wshadow=global`, `-Wshadow=local`, and `-Wshadow=compatible-local`.

## External Linking

- Only use `extern` for global variable forward declarations or const global variable definitions. Do not use `extern` for non-const global variables as they are implicitly extern.

- Examples below:
~~~C++
// Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
~~~

- Be aware of the *static initialization order fiasco* - you cannot know in what order globals will be initialized

- Avoid initializing objects with static duration using other objects with static duration from a different translation unit

## Inline

- Modern use of the term `inline` is for functions to be allowed to have multiple defintions and is typically done in header files
  - The linker will consolidate all inline function definitions into a single definition

- The following are implicitly inline
  - Functions defined inside a class, struct, or union type definition
  - Constexpr / consteval functions
  - Functions implicitly instantiated from function templates

- If you need global constants and your compiler is C++17 capable, prefer defining `inline constexpr` global variables in a header file 

## Static vars

- Static local variables are best used to avoid expensive local object initialization each time a function is called
- Do not use static local variables to modify function flow

## Scope, Duration, Linkage

| Type                                      | Example                         | Scope   | Duration | Linkage   | Notes                                |
|-------------------------------------------|----------------------------------|---------|----------|-----------|--------------------------------------|
| Local variable                             | `int x;`                         | Block   | Automatic| None      |                                      |
| Static local variable                      | `static int s_x;`                | Block   | Static   | None      |                                      |
| Dynamic local variable                     | `int* x { new int{} };`          | Block   | Dynamic  | None      |                                      |
| Function parameter                         | `void foo(int x)`                | Block   | Automatic| None      |                                      |
| Internal non-const global variable         | `static int g_x;`                | Global  | Static   | Internal  | Initialized or uninitialized         |
| External non-const global variable         | `int g_x;`                       | Global  | Static   | External  | Initialized or uninitialized         |
| Inline non-const global variable (C++17)   | `inline int g_x;`                | Global  | Static   | External  | Initialized or uninitialized         |
| Internal constant global variable          | `constexpr int g_x { 1 };`       | Global  | Static   | Internal  | Must be initialized                  |
| External constant global variable          | `extern const int g_x { 1 };`    | Global  | Static   | External  | Must be initialized                  |
| Inline constant global variable (C++17)    | `inline constexpr int g_x { 1 };`| Global  | Static   | External  | Must be initialized                  |

| Type                              | Example                       | Notes                                          |
|-----------------------------------|-------------------------------|------------------------------------------------|
| Function forward declaration      | `void foo(int x);`            | Prototype only, no function body               |
| Non-constant variable forward declaration | `extern int g_x;`           | Must be uninitialized                          |
| Const variable forward declaration       | `extern const int g_x;`     | Must be uninitialized                          |
| Constexpr variable forward declaration   | `extern constexpr int g_x;` | Not allowed, `constexpr` cannot be forward declared |

- Prefer `using Foo::var` over `using namespace Foo` to avoid name collisions

## Random

- Be wary of improperly seeding a random number generator
- Use the following header for programs:

~~~C++
#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
~~~

## Std::cin Validation

- Use the below example program to see 3 elements of input validation needed

~~~C++
#include <cstdlib> // for std::exit
#include <iostream>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        if (y == 0.0)
            break;

        std::cout << x / y << '\n';
        return;
    }

    std::cout << "???";  // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    // Handle division by 0
    while (operation == '/' && y == 0.0)
    {
        std::cout << "The denominator cannot be zero.  Try again.\n";
        y = getDouble();
    }

    printResult(x, operation, y);

    return 0;
}
~~~

## Arithmetic conversions

- Be wary of comparing unsigned integers with signed integers. Weird results happen due to the *usual arithmetic rules*
- Look out for narrowing conversions. Some, for example a constexpr to float, don't trigger a compiler error
- Can use `std::common_type_t<int, double>` from the `type_traits` header to find out two types common type


