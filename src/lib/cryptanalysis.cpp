#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

#include "src/lib/cryptanalysis.hpp"
#include "src/lib/english.hpp"
#include "src/lib/utils.hpp"

// Single-byte XOR
MaxScoreResults breakSingleByteXOR(std::span<const uint8_t> bytes) {
  int bestScore = -1;
  uint8_t bestKey = 0;
  std::vector<uint8_t> bestCandidate;
  for (int keyIndex = 0; keyIndex < 256; ++keyIndex) {
    uint8_t key = static_cast<uint8_t>(keyIndex);
    std::vector<uint8_t> candidate(bytes.begin(), bytes.end());
    singleByteXOR(candidate, key);
    int score = letterFrequencyScore(candidate);
    if (score > bestScore) {
      bestScore = score;
      bestKey = key;
      bestCandidate = std::move(candidate);
    }
  }
  return {bestScore, bestKey, bestCandidate};
}

// Vigenere's Cipher
double avgHammingDist(std::span<const uint8_t> buffer, size_t keySize) {
  assert(2 * keySize <= buffer.size());

  size_t blocks = std::min(buffer.size() / keySize, static_cast<size_t>(4));
  int totalDist = 0;
  for (size_t i = 0; i < blocks - 1; ++i) {
    auto span1 = std::span(buffer).subspan(i * keySize, keySize);
    for (size_t j = i + 1; j < blocks; ++j) {
      auto span2 = std::span(buffer).subspan(j * keySize, keySize);
      auto dist = findHammingDist(span1, span2);
      if (dist) {
        totalDist += *dist;
      }
    }
  }
  size_t iterations = (blocks * (blocks - 1)) / 2;
  return static_cast<double>(totalDist) / iterations;
}

size_t findKeySize(std::span<const uint8_t> buffer) {
  double smallestDist = static_cast<double>(buffer.size()) / 2 * 8;
  size_t keySize = 0;
  for (size_t i = 2; i < buffer.size() / 2 && i < 40; ++i) {
    double dist = avgHammingDist(buffer, i);
    double normalizedDist = dist / i;
    if (normalizedDist < smallestDist) {
      smallestDist = normalizedDist;
      keySize = i;
    }
  }
  return keySize;
}

std::vector<uint8_t> breakVigenere(std::span<const uint8_t> buffer,
                                   size_t keySize) {
  std::vector<uint8_t> key;
  key.reserve(keySize);
  size_t blocks = buffer.size() / keySize;
  for (size_t i = 0; i < keySize; ++i) {
    std::vector<uint8_t> transposed;
    for (size_t blockNum = 0; blockNum < blocks; ++blockNum) {
      transposed.push_back(buffer[blockNum * keySize + i]);
    }
    auto [bestScore, bestKey, bestCandidate] = breakSingleByteXOR(transposed);
    key.push_back(bestKey);
  }
  return key;
}
