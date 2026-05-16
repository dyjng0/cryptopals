#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/aes.hpp"
#include "src/lib/encoding.hpp"

static constexpr std::array<uint8_t, 16> key = {'Y', 'E', 'L', 'L', 'O', 'W',
                                                ' ', 'S', 'U', 'B', 'M', 'A',
                                                'R', 'I', 'N', 'E'};

int challenge2_10(int argc, char **argv) {
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
    std::cerr << "Usage ./cryptopals 2-10 OR ./cryptopals 2-10 <base64>\n";
    return 1;
  }

  std::vector<uint8_t> buffer = stringToBytes(input);
  encryptAES_ECB(buffer, key);
  std::cout << bytesToBase64(buffer) << '\n';
  return 0;
}
