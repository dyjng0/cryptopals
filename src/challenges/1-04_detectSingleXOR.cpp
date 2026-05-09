#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"

int challenge1_04(int argc, char **argv) {
  std::string fileName, fileText;

  if (argc == 1) {
    fileName = "resources/1-04.txt";
  } else if (argc == 2) {
    fileName = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-04 OR ./cryptopals 1-04 <filename>\n";
    return 1;
  }

  int bestScore = -1;
  std::vector<uint8_t> bestCandidate;
  std::ifstream readFile(fileName);
  while (getline(readFile, fileText)) {
    auto bytes = hexToBytes(fileText);
    if (!bytes) {
      std::cerr << "Error: invalid hex string.\n";
      return 1;
    }
    auto [score, key, candidate] = breakSingleByteXOR(*bytes);
    if (score > bestScore) {
      bestScore = score;
      bestCandidate = candidate;
    }
  }
  std::cout << bytesToString(bestCandidate);
  return 0;
}
