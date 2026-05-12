#include <fstream>
#include <iostream>
#include <string>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"

int challenge1_06(int argc, char **argv) {
  std::string input = "";
  if (argc == 1) {
    std::string fileName, fileText;
    fileName = "resources/1-06.txt";
    std::ifstream readFile(fileName);
    while (getline(readFile, fileText)) {
      input += fileText;
    }
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-06 OR ./cryptopals 1-06 <base64>\n";
    return 1;
  }

  auto bytes = base64ToBytes(input);
  if (!bytes) {
    std::cerr << "Error: invalid base64.\n";
    return 1;
  }
  int keySize = findKeySize(*bytes);
  std::vector<uint8_t> decrypted = breakVigenere(*bytes, keySize);
  std::cout << bytesToString(decrypted) << '\n';
  return 0;
}
