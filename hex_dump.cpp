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
#include <iostream>
#include <iomanip>

std::string generateAddress() {
    static int hexAddress {0x0};
    std::ostringstream strAddress;
    strAddress << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << hexAddress;
    hexAddress += 16; // Increment after to start from 0x00
    return strAddress.str();
}

std::string hexdump(const std::vector<char> &data){
    // Read in first 16 bytes
    // Generate memory address
    // convert first 16 bytes of hexadecimal into a <string>
    // convert hexadecimal with values between ASCII value 32 and 126 to their ASCII translation
    // Append memory address + 16 bytes + ASCII translations together

std::ostringstream hexout;

for (size_t i = 0; i < data.size(); i += 16) {
    // Print address
    hexout << std::hex << std::nouppercase
           << std::setw(8) << std::setfill('0') << i << ":";

    // Print hex bytes
    for (int j = 0; j < 16; ++j) {
        hexout << " ";
        if (i + j < data.size()) {
            hexout << std::setw(2) << std::setfill('0')
                   << static_cast<int>(static_cast<unsigned char>(data[i + j]));
        } else {
            hexout << "  ";
        }
    }

    // Two spaces between hex and ASCII block
    hexout << "  ";

    // ASCII block
    for (int j = 0; j < 16 && i + j < data.size(); ++j) {
        char c = data[i + j];
        hexout << ((c >= 32 && c <= 126) ? c : '.');
    }

    if (i + 16 < data.size()) {
        hexout << "\n";  // only if it's not the last line
    }
}
return hexout.str();
}


std::vector<char> dehex(const std::string &text){
    std::vector<char> result;
    std::istringstream iss(text);
    std::string line;

    while (std::getline(iss, line)) {
        // Skip the address at the beginning (first 10 characters: 8 digits + ": ")
        if (line.size() < 10) continue;

        size_t pos = 10;
        int byteCount = 0;

        while (byteCount < 16 && pos + 1 < line.size()) {
            // Skip spaces
            while (pos < line.size() && line[pos] == ' ')
                ++pos;

            // Stop if we're at the ASCII section (2 spaces before it)
            if (pos + 1 >= line.size() || !std::isxdigit(line[pos]) || !std::isxdigit(line[pos + 1]))
                break;

            std::string byteStr = line.substr(pos, 2);
            char byte = static_cast<char>(std::stoi(byteStr, nullptr, 16));
            result.push_back(byte);

            pos += 2;
            ++byteCount;
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    const std::vector<char> testData1{	
            0x1d, (char)0xc4, 0x15, 0x25, (char)0x91, (char)0xe6, 0x09, 0x59,
            0x04, (char)0x99, 0x15, 0x29, 0x0a, 0x45, 0x21, 0x29,
            0x26, (char)0x8e, 0x74, (char)0xa0, 0x1a, (char)0xbe, 0x75, 0x68,
            0x06, (char)0xdd, 0x70, 0x33, (char)0xa4, 0x77, 0x7a, 0x5d,
            (char)0xb1, (char)0xba, 0x22, (char)0xa7, (char)0xcf, (char)0xcc, (char)0xf7, (char)0xef,
            (char)0xb1, (char)0xe3, 0x13, (char)0xed, (char)0xf1, (char)0x89, (char)0xad, (char)0xad,
            (char)0xb8, 0x2a, 0x52, 0x32, 0x65, 0x79, 0x43, (char)0x99,
            0x6f, (char)0xc8, (char)0xd3, (char)0x8e, (char)0xb2, 0x5f, 0x50, (char)0xc9,
            0x08, 0x4a, 0x12, 0x25, 0x79, (char)0xc2, (char)0xdd, 0x31,
            0x6b, (char)0xb8, 0x77, 0x74, 0x4b, 0x68, 0x4b, (char)0xd4,
            (char)0xdb, 0x4e, (char)0x92, 0x09, (char)0xd5, 0x4c, (char)0x9f, 0x0b,
            (char)0xfd, (char)0xa9, (char)0xd1, (char)0xd6, 0x13, (char)0xf5, (char)0xf8, (char)0x81
			};
    
    std::cout << hexdump(testData1);
    return 0;
}