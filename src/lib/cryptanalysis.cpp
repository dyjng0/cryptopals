#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "src/lib/cryptanalysis.hpp"
#include "src/lib/english.hpp"
#include "src/lib/utils.hpp"

// Single-byte XOR
MaxScoreResults breakSingleByteXOR(const std::vector<uint8_t> &bytes) {
  int bestScore = -1;
  uint8_t bestKey = 0;
  std::vector<uint8_t> bestCandidate;
  for (int keyIndex = 0; keyIndex < 256; keyIndex++) {
    uint8_t key = static_cast<uint8_t>(keyIndex);
    std::vector<uint8_t> candidate = bytes;
    singleByteXOR(candidate, key);
    int score = letterFrequencyScore(candidate);
    if (score > bestScore) {
      bestScore = score;
      bestKey = key;
      bestCandidate = candidate;
    }
  }
  return {bestScore, bestKey, bestCandidate};
}

// Vigenere's Cipher
std::optional<double> avgHammingDist(const std::vector<uint8_t> &buffer,
                                     int keySize) {
  if (static_cast<size_t>(2 * keySize) > buffer.size()) {
    return std::nullopt;
  }

  int blocks = std::min(buffer.size() / keySize, static_cast<size_t>(4));
  int totalDist = 0;
  for (int i = 0; i < blocks - 1; i++) {
    std::vector<uint8_t> buffer1(buffer.begin() + i * keySize,
                                 buffer.begin() + (i + 1) * keySize);
    for (int j = i; j < blocks; j++) {
      std::vector<uint8_t> buffer2(buffer.begin() + j * keySize,
                                   buffer.begin() + (j + 1) * keySize);
      auto dist = findHammingDist(buffer1, buffer2);
      if (!dist) {
        continue;
      }
      totalDist += *dist;
    }
  }
  int iterations = (blocks * (blocks - 1)) / 2;
  return static_cast<double>(totalDist) / iterations;
}

int findKeySize(const std::vector<uint8_t> &buffer) {
  double smallestDist = std::max((int)(buffer.size() / 2), 40) * 8;
  int keySize = 0;
  for (size_t i = 2; i < buffer.size() / 2 && i < 40; i++) {
    auto dist = avgHammingDist(buffer, i);
    if (dist) {
      double normalizedDist = *dist / i;
      if (normalizedDist < smallestDist) {
        smallestDist = normalizedDist;
        keySize = i;
      }
    }
  }
  return keySize;
}

std::vector<uint8_t> breakVigenere(const std::vector<uint8_t> &buffer,
                                   int keySize) {
  std::vector<uint8_t> key;
  key.reserve(keySize);
  int blocks = buffer.size() / keySize;
  for (int i = 0; i < keySize; i++) {
    std::vector<uint8_t> transposeBlock;
    for (int blockNum = 0; blockNum < blocks; blockNum++) {
      transposeBlock.push_back(buffer[blockNum * keySize + i]);
    }
    auto [bestScore, bestKey, bestCandidate] =
        breakSingleByteXOR(transposeBlock);
    key.push_back(bestKey);
  }
  return key;
}
