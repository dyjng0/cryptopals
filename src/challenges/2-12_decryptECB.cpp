#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/oracles.hpp"

int challenge2_12(int argc, char **argv) {
  std::string input = "";
  if (argc == 1) {
    input = "YWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYSA=";
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 2-12  OR ./cryptopals <base64>\n";
    return 1;
  }
  auto buffer = base64ToBytes(input);
  if (!buffer) {
    std::cerr << "Error: invalid base64.\n";
    return 1;
  }
  std::vector<uint8_t> ciphertext = ecbEncryptionOracle(*buffer);
  std::cout << "Ciphertext: " << bytesToHex(ciphertext) << '\n';
  return 0;
}
