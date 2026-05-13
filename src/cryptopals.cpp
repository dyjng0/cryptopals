#include "challenges/challenges.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

using ChallengeFunc = std::function<int(int, char **)>;
const std::unordered_map<std::string, ChallengeFunc> challenges = {
    {"1-01", challenge1_01},
    {"1-02", challenge1_02},
    {"1-03", challenge1_03},
    {"1-04", challenge1_04},
    {"1-05", challenge1_05},
    {"1-06", challenge1_06},
    {"1-07", challenge1_07},
    {"1-08", challenge1_08},
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: ./cryptopals <challenge> [args...]\n";
    return 1;
  }

  std::string challenge = argv[1];
  auto it = challenges.find(challenge);
  if (it != challenges.end()) {
    return it->second(argc - 1, argv + 1);
  }
  std::cerr << "Unknown challenge: " << challenge << '\n';
  return 1;
}
