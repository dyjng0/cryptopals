#include <iostream>
#include <string>
#include <unordered_map>

#include "src/challenges/challenges.hpp"
#include "src/lib/utils.hpp"

int challenge2_13(int argc, char **argv) {
  std::string input = "foo=bar&baz=qux&zap=zazzle";
  std::unordered_map<std::string, std::string> map = parseKV(input);
  for (auto i : map) {
    std::cout << i.first << ": " << i.second << std::endl;
  }
  return 0;
}
