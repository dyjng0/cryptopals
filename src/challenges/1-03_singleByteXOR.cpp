#include <iostream>

#include "src/challenges/challenges.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/encoding.hpp"

int challenge1_03(int argc, char *argv[]) {
  std::string input;

  if (argc == 1) {
    input =
        "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  } else if (argc == 2) {
    input = argv[1];
  } else {
    std::cerr << "Usage ./cryptopals 1-03 OR ./cryptopals 1-03 <hexString>\n";
    return 1;
  }

  auto bytes = hexToBytes(input);
  if (!bytes) {
    std::cerr << "Error: invalid hex string.\n";
    return 1;
  }
  auto [maxScore, bestKey, maxScoreXOR] = breakSingleByteXOR(*bytes);
  std::string result = bytesToString(maxScoreXOR);
  std::cout << result << '\n';
  return 0;
}
