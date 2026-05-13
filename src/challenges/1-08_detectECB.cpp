#include <fstream>
#include <iostream>
#include <string>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"

int challenge1_08(int argc, char **argv) {
  std::string fileName, fileText;

  if (argc == 1) {
    fileName = "resources/1-08.txt";
  } else if (argc == 2) {
    fileName = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-08 OR ./cryptopals 1-06 <filename>\n";
    return 1;
  }

  int bestScore = -1;
  std::string bestCandidate;
  std::ifstream readFile(fileName);
  while (getline(readFile, fileText)) {
    auto bytes = hexToBytes(fileText);
    if (!bytes) {
      std::cerr << "Error: invalid hex string.\n";
      return 1;
    }
    int score = getECBScore(*bytes);
    if (score > bestScore) {
      bestScore = score;
      bestCandidate = fileText;
    }
  }
  std::cout << bestCandidate << '\n';
  return 0;
}
