#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/utils.hpp"

int challenge1_05(int argc, char **argv) {
  std::string plaintext;

  if (argc == 1) {
    plaintext = "Burning 'em, if you ain't quick and nimble\nI go "
                "crazy when I hear a cymbal";
  } else if (argc == 2) {
    plaintext = argv[1];
  } else {
    std::cerr << "Usage: ./cryptopals 1-05 OR ./cryptopals 1-05 <plaintext>\n";
    return 1;
  }

  std::string key = "ICE";
  std::vector<uint8_t> byteKey = stringToBytes(key);
  std::cout << bytesToHex(repeatingKeyXOR(stringToBytes(plaintext), byteKey))
            << '\n';
  return 0;
}
