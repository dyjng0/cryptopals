#pragma once

#include <cstdint>
#include <functional>
#include <span>
#include <string>
#include <vector>

struct MaxScoreResults {
  int bestScore;
  uint8_t bestKey;
  std::vector<uint8_t> bestCandidate;
};
using ecbOracle = std::function<std::vector<uint8_t>(std::span<const uint8_t>)>;

MaxScoreResults breakSingleByteXOR(std::span<const uint8_t> bytes);

double avgHammingDist(std::span<const uint8_t> buffer, size_t keySize);
size_t findKeySize(std::span<const uint8_t> buffer);
std::vector<uint8_t> breakVigenere(std::span<const uint8_t> buffer,
                                   size_t keySize);

int getECBScore(std::span<const uint8_t> buffer);
std::string detectCBCorECB(std::span<const uint8_t> ciphertext);
size_t findBlockSize(ecbOracle oracle, uint8_t padChar,
                     std::span<const uint8_t> plaintext);
