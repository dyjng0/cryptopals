#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "src/challenges/challenges.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/english.hpp"

int challenge1_06(int argc, char **argv) {
  std::string s1, s2;

  if (argc == 1) {
    s1 = "this is a test";
    s2 = "wokka wokka!!!";
  }

  std::vector<uint8_t> buffer1 = stringToBytes(s1);
  std::vector<uint8_t> buffer2 = stringToBytes(s2);
  auto hammingDist = findHammingDist(buffer1, buffer2);
  std::cout << *hammingDist << '\n';
  return 0;
}
