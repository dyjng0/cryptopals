#pragma once

#include <cstdint>
#include <vector>

struct MaxScoreResults {
  int bestScore;
  uint8_t bestKey;
  std::vector<uint8_t> bestCandidate;
};

MaxScoreResults breakSingleByteXOR(const std::vector<uint8_t> &bytes);

double avgHammingDist(const std::vector<uint8_t> &buffer, size_t keySize);
size_t findKeySize(const std::vector<uint8_t> &buffer);
std::vector<uint8_t> breakVigenere(const std::vector<uint8_t> &buffer,
                                   size_t keySize);
