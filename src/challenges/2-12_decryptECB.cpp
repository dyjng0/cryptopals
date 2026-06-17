#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/oracles.hpp"

int challenge2_12(int argc, char **argv) {
  std::string input = "";
  if (argc == 1) {
    input = "Yerr";
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

  size_t blockSize = findBlockSize(ecbEncryptionOracle, *buffer);
  std::vector<uint8_t> testInput(2 * blockSize, 'A');
  std::vector<uint8_t> ciphertext = ecbEncryptionOracle(testInput);
  if (!isECB(ciphertext)) {
    std::cerr << "Error: must be encoded in ECB mode.\n";
    return 1;
  }

  std::cout << "ECB mode!" << '\n';
  return 0;
}
