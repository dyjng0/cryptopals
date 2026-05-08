#include <iostream>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"

int challenge1_01(int argc, char *argv[]) {
  std::string input;

  if (argc == 1) {
    input = "49276d206b696c6c696e6720796f757220627261696e206c696b65"
            "206120706f69736f6e6f7573206d757368726f6f6d";
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage: ./cryptopals 1-01 OR ./cryptopals 1-01 <hexString>\n";
    return 1;
  }

  auto bytes = hexToBytes(input);
  if (!bytes) {
    std::cerr << "Error: invalid hex string.\n";
    return 1;
  }
  std::string result = bytesToBase64(*bytes);
  std::cout << result << '\n';
  return 0;
}
