#include <cstdint>
#include <iostream>
#include <string>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/oracles.hpp"

int challenge2_11(int argc, char **argv) {
  std::string input = "";
  if (argc == 1) {
    // 11 + 16 + 16 blocks of 'a' in base64
    // if in ECB, second and third block must be the same
    input = "YWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYWFhYSA=";
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 2-11 OR ./cryptopals 2-11 <base64>\n";
    return 1;
  }

  auto buffer = base64ToBytes(input);
  if (!buffer) {
    std::cerr << "Error: invalid base64.\n";
    return 1;
  }
  std::vector<uint8_t> ciphertext = modeEncryptionOracle(*buffer);
  bool mode = isECB(ciphertext);

  std::cout << "Ciphertext: " << bytesToHex(ciphertext) << '\n';
  if (mode) {
    std::cout << "Detected: ECB" << '\n';
  } else {
    std::cout << "Detected: CBC" << '\n';
  }
  return 0;
}
