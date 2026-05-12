#include <fstream>
#include <iostream>
#include <span>
#include <string>

#include "src/challenges/challenges.hpp"
#include "src/lib/aes.hpp"
#include "src/lib/encoding.hpp"

static constexpr std::array<uint8_t, 16> key = {'Y', 'E', 'L', 'L', 'O', 'W',
                                                ' ', 'S', 'U', 'B', 'M', 'A',
                                                'R', 'I', 'N', 'E'};

int challenge1_07(int argc, char **argv) {
  std::string input = "";
  if (argc == 1) {
    std::string fileName, fileText;
    fileName = "resources/1-07.txt";
    std::ifstream readFile(fileName);
    while (getline(readFile, fileText)) {
      input += fileText;
    }
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-07 OR ./cryptopals 1-06 <base64>\n";
    return 1;
  }

  auto buffer = base64ToBytes(input);
  if (!buffer) {
    std::cerr << "Error: invalid base64.\n";
    return 1;
  }
  decryptAES(*buffer, key);
  std::cout << bytesToString(*buffer) << '\n';
  return 0;
}
