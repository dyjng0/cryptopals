#include <iostream>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/utils.hpp"

int challenge1_02(int argc, char *argv[]) {
  std::string buf1, buf2;

  if (argc == 1) {
    buf1 = "1c0111001f010100061a024b53535009181c";
    buf2 = "686974207468652062756c6c277320657965";
  } else if (argc == 3) {
    buf1 = argv[1];
    buf2 = argv[2];
  } else {
    std::cerr << "Usage: ./cryptopals 1-02 OR ./cryptopals 1-02 <buffer1> "
                 "<buffer2>\n";
    return 1;
  }

  auto bytes1 = hexToBytes(buf1);
  auto bytes2 = hexToBytes(buf2);
  if (!bytes1 || !bytes2) {
    std::cerr << "Error: Invalid hex string.\n";
    return 1;
  }
  auto xor_opt = fixedXOR(*bytes1, *bytes2);
  if (!xor_opt) {
    std::cerr << "Error: Buffers must be of equal length.\n";
    return 1;
  }
  std::string result = bytesToHex(*xor_opt);
  std::cout << result << '\n';
  return 0;
}
