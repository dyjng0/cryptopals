#include <fstream>
#include <iostream>
#include <string>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/english.hpp"

int challenge1_06(int argc, char **argv) {
  std::string fileName, fileText;

  if (argc == 1) {
    fileName = "resources/1-06.txt";
  } else if (argc == 2) {
    fileName = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-06 OR ./cryptopals 1-06 <fileName>\n";
    return 1;
  }

  std::string fullText = "";
  std::ifstream readFile(fileName);
  while (getline(readFile, fileText)) {
    fullText += fileText;
  }

  auto bytes = base64ToBytes(fullText);
  if (!bytes) {
    std::cerr << "Error: invalid base64.\n";
    return 1;
  }
  int keySize = findKeySize(*bytes);
  std::vector<uint8_t> decrypted = decryptVigenere(*bytes, keySize);
  std::string decryptedString = bytesToString(decrypted);
  std::cout << decryptedString << '\n';
  return 0;
}
