// Create a parser to interpret and execute the Deadfish language.

// Deadfish operates on a single value in memory, which is initially set to 0.

// It uses four single-character commands:

// i: Increment the value
// d: Decrement the value
// s: Square the value
// o: Output the value to a result array
// All other instructions are no-ops and have no effect.

// Examples
// Program "iiisdoso" should return numbers [8, 64].
// Program "iiisdosodddddiso" should return numbers [8, 64, 3600].

#include <vector>
#include <string_view>
#include <unordered_map>
#include <functional>
#include <unordered_set>

std::vector<int> parse(std::string_view data) {
    // Instantiate initial value
    int original_value {0};
    // Instantiate output vector
    std::vector<int> output;
    // Instantiate map to store single character commands
    std::unordered_map<char, std::function<int(int)>> commands;
    // Add single character commands as lambdas
    commands['i'] = [](int x){return x + 1;};
    commands['d'] = [](int x){return x - 1;};
    commands['s'] = [](int x){return x * x;};
    // Loop through all character commands in data argument, executing them on the initial value and or outputting it to a result array
    std::unordered_set<char> valid_ops {'i', 'd', 's', 'o'};

    for (auto &&i : data)
    {
        if (valid_ops.find(i) != valid_ops.end())
        {
            if (i == 'o')
            {
                output.push_back(original_value);
            }
            else
            {
                original_value = commands[i](original_value);
            } 
        }
    }
    return output;
}