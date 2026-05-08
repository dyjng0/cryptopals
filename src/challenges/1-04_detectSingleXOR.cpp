#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/english.hpp"

int challenge1_04(int argc, char **argv) {
  std::string fileText;
  std::string fileName;

  if (argc == 1) {
    fileName = "resources/1-04.txt";
  } else if (argc == 2) {
    fileName = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-04 OR ./cryptopals 1-04 <fileName>\n";
    return 1;
  }

  int bestScore = -1;
  std::vector<uint8_t> bestXOR;
  std::ifstream readFile(fileName);
  while (getline(readFile, fileText)) {
    auto bytes = hexToBytes(fileText);
    if (!bytes) {
      std::cerr << "Error: invalid hex string.\n";
      return 1;
    }
    auto [maxScore, bestKey, maxScoreXOR] = testKeys(*bytes);
    if (maxScore > bestScore) {
      bestScore = maxScore;
      bestXOR = maxScoreXOR;
    }
  }
  std::string result = bytesToString(bestXOR);
  std::cout << result;
  return 0;
}
