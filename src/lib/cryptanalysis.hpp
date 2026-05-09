#pragma once

#include <cstdint>
#include <optional>
#include <vector>

struct MaxScoreResults {
  int bestScore;
  uint8_t bestKey;
  std::vector<uint8_t> bestCandidate;
};

MaxScoreResults breakSingleByteXOR(std::vector<uint8_t> &bytes);

std::optional<double> avgHammingDist(const std::vector<uint8_t> &buffer,
                                     int keySize);
int findKeySize(const std::vector<uint8_t> &buffer);
std::vector<uint8_t> breakVigenere(const std::vector<uint8_t> &buffer,
                                   int keySize);
