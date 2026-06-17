#include <cstdint>
#include <iostream>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/oracles.hpp"

int challenge2_12(int argc, char **argv) {
  if (argc == 2) {
    auto buffer = base64ToBytes(argv[1]);
    if (!buffer) {
      std::cerr << "Error: invalid base64.\n";
      return 1;
    }
    std::vector<uint8_t> ciphertext = ecbEncryptionOracle(*buffer);
    std::cout << "Ciphertext: " << bytesToHex(ciphertext) << '\n';
  }
  if (argc > 2) {
    std::cerr << "Usage ./cryptopals 2-12 OR ./cryptopals 2-12 <base64>\n";
    return 1;
  }

  size_t blockSize = findBlockSize(ecbEncryptionOracle);
  std::vector<uint8_t> testInput(2 * blockSize, 'A');
  std::vector<uint8_t> ciphertext = ecbEncryptionOracle(testInput);
  if (!isECB(ciphertext)) {
    std::cerr << "Error: must be encoded in ECB mode.\n";
    return 1;
  }

  std::vector<uint8_t> plaintext;
  size_t plaintextSize = findPlaintextSize(ecbEncryptionOracle);
  for (size_t i = 0; i < plaintextSize; ++i) {
    auto byte =
        decryptByteAtIndex(ecbEncryptionOracle, blockSize, i, plaintext);
    if (!byte) {
      std::cout << "Error: no match found for index " << i << '\n';
      return 1;
    }
    plaintext.push_back(*byte);
  }
  std::cout << bytesToString(plaintext);
  return 0;
}
