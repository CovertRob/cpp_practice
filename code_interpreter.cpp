// Inspired from real-world Brainf**k, we want to create an interpreter of that language which will support the following instructions:

// > increment the data pointer (to point to the next cell to the right).
// < decrement the data pointer (to point to the next cell to the left).
// + increment (increase by one, truncate overflow: 255 + 1 = 0) the byte at the data pointer.
// - decrement (decrease by one, treat as unsigned byte: 0 - 1 = 255 ) the byte at the data pointer.
// . output the byte at the data pointer.
// , accept one byte of input, storing its value in the byte at the data pointer.
// [ if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
// ] if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
// The function will take in input...

// the program code, a string with the sequence of machine instructions,
// the program input, a string, possibly empty, that will be interpreted as an array of bytes using each character's ASCII code and will be consumed by the , instruction
// ... and will return ...

// the output of the interpreted code (always as a string), produced by the . instruction.
// Implementation-specific details for this Kata:

// Your memory tape should be large enough - the original implementation had 30,000 cells but a few thousand should suffice for this Kata
// Each cell should hold an unsigned byte with wrapping behavior (i.e. 255 + 1 = 0, 0 - 1 = 255), initialized to 0
// The memory pointer should initially point to a cell in the tape with a sufficient number (e.g. a few thousand or more) of cells to its right. For convenience, you may want to have it point to the leftmost cell initially
// You may assume that the , command will never be invoked when the input stream is exhausted
// Error-handling, e.g. unmatched square brackets and/or memory pointer going past the leftmost cell is not required in this Kata. If you see test cases that require you to perform error-handling then please open an Issue in the Discourse for this Kata (don't forget to state which programming language you are attempting this Kata in).

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

std::string brainLuck(const std::string& code, const std::string& input) {
    const int TAPE_SIZE = 30000;
    std::vector<unsigned char> tape(TAPE_SIZE, 0);  // memory tape
    std::string output;

    int data_ptr = 0;
    int code_ptr = 0;
    int input_ptr = 0;

    std::unordered_map<int, int> bracket_map;
    std::stack<int> loop_stack;

    // Precompute matching brackets
    for (int i = 0; i < code.length(); ++i) {
        if (code[i] == '[') {
            loop_stack.push(i);
        } else if (code[i] == ']') {
            int open = loop_stack.top();
            loop_stack.pop();
            bracket_map[open] = i;
            bracket_map[i] = open;
        }
    }

    // Interpret the code
    while (code_ptr < code.length()) {
        char command = code[code_ptr];

        switch (command) {
            case '>':
                ++data_ptr;
                break;
            case '<':
                --data_ptr;
                break;
            case '+':
                tape[data_ptr] = (tape[data_ptr] + 1) % 256;
                break;
            case '-':
                tape[data_ptr] = (tape[data_ptr] - 1 + 256) % 256;
                break;
            case '.':
                output += static_cast<char>(tape[data_ptr]);
                break;
            case ',':
                tape[data_ptr] = static_cast<unsigned char>(input[input_ptr++]);
                break;
            case '[':
                if (tape[data_ptr] == 0)
                    code_ptr = bracket_map[code_ptr];
                break;
            case ']':
                if (tape[data_ptr] != 0)
                    code_ptr = bracket_map[code_ptr];
                break;
        }

        ++code_ptr;
    }

    return output;
}
