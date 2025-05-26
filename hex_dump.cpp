// Your Task
// Your task is to complete the functions hexdump and dehex:

// hexdump takes a vector<char> and returns a hex dump (as a string) in the following format:

// the memory address displayed as an 8-digit hexadecimal number (starting from 00000000), followed by a colon (:) and a space,
// 16 bytes displayed as 2-digit hexadecimal numbers, separated by a space,
// two spaces,
// the ASCII translation of the bytes if the ASCII values are between 32 and 126 (both included), otherwise a full stop (.)
// Note: all hexadecimal values (data and addresses) should be presented in lowercase

// If the last line is shorter than 16 bytes, then replace the byte values with spaces, but trim the trailing spaces from the end of the line.

// For example:

// 00000000: 1d c4 15 25 91 e6 09 59 04 99 15 29 0a 45 21 29  ...%...Y...).E!)
// 00000010: 26 8e 74 a0 1a be 75 68 06 dd 70 33 a4 77 7a 5d  &.t...uh..p3.wz]
// 00000020: b1 ba 22 a7 cf cc f7 ef b1 e3 13 ed f1 89 ad ad  ..".............
// 00000030: b8 2a 52 32 65 79 43 99 6f c8 d3 8e b2 5f 50 c9  .*R2eyC.o...._P.
// 00000040: 08 4a 12 25 79 c2 dd 31 6b b8 77 74 4b 68 4b d4  .J.%y..1k.wtKhK.
// 00000050: db 4e 92 09 d5 4c 9f 0b fd a9 d1                 .N...L.....
// dehex takes a string input, in the same format as the output described above, and returns vector<char>.

// Note: all inputs will be valid, so validating it is not necessary.

// The memory addresses are created by my functions starting at 8 digit hexadecimal number at 0. Then increment from there for every 16 bytes

// Problem:
//     Need to read in a vector<char> and for every 16 bytes assign it a memory address and conduct an ASCII translation for the values that are between 32 and 126, inclusive.
//      Input: vector<char> is in hexadecimal format already
//      Helpers to input:
//          - Memory address generator
//          - hexadecimal stored via char to ASCII value converter

#include <string>
#include <vector>



std::string hexdump(const std::vector<char> &data){
    // Read in first 16 bytes
    // Generate memory address
    // convert first 16 bytes of hexadecimal into a <string>
    // convert hexadecimal with values between ASCII value 32 and 126 to their ASCII translation
    // Append memory address + 16 bytes + ASCII translations together
};


std::vector<char> dehex(const std::string &text){

};