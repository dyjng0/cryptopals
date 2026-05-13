#pragma once

#include <cstdint>
#include <span>
#include <vector>

struct MaxScoreResults {
  int bestScore;
  uint8_t bestKey;
  std::vector<uint8_t> bestCandidate;
};

MaxScoreResults breakSingleByteXOR(std::span<const uint8_t> bytes);

double avgHammingDist(std::span<const uint8_t> buffer, size_t keySize);
size_t findKeySize(std::span<const uint8_t> buffer);
std::vector<uint8_t> breakVigenere(std::span<const uint8_t> buffer,
                                   size_t keySize);

int getECBScore(std::span<const uint8_t> buffer);
