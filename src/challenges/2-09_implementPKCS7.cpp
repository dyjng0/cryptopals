#include <cstdint>
#include <iostream>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/aes.hpp"
#include "src/lib/encoding.hpp"

int challenge2_09(int argc, char **argv) {
  std::string input = "";
  if (argc == 1) {
    input = "YELLOW SUBMARINE";
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 2-09 OR ./cryptopals 2-09 <string>\n";
    return 1;
  }

  std::vector<uint8_t> bytes = stringToBytes(input);
  std::vector<uint8_t> paddedBytes = padPKCS7(bytes);
  std::cout << bytesToString(paddedBytes);
  return 0;
}
