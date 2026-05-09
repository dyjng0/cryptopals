#include <cmath>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

#include "src/lib/encoding.hpp"
#include "src/lib/english.hpp"

static constexpr int LETTER_FREQUENCY[26] = {
    855, 160, 316, 387, 1210, 218, 209, 496, 733, 22,  81, 421, 253,
    717, 747, 207, 10,  633,  673, 894, 268, 106, 183, 19, 172, 11};

std::optional<int> getLetterIndex(const uint8_t byte) {
  if (byte >= 'a' && byte <= 'z') {
    return static_cast<int>(byte - 'a');
  } else if (byte >= 'A' && byte <= 'Z') {
    return static_cast<int>(byte - 'A');
  }
  return std::nullopt;
}

int letterFrequencyScore(const std::vector<uint8_t> &bytes) {
  int score = 0;
  for (uint8_t byte : bytes) {
    auto letterIndex = getLetterIndex(byte);
    if (letterIndex) {
      score += LETTER_FREQUENCY[*letterIndex];
    } else if (byte == ' ') {
      score += 1300;
    } else if (byte < 32 || byte > 126) {
      score -= 5000;
    }
  }
  return score;
}

MaxScoreResults testKeys(const std::vector<uint8_t> &bytes) {
  int maxScore = -1;
  uint8_t bestKey = 0;
  std::vector<uint8_t> maxScoreXOR;
  for (int keyIndex = 0; keyIndex < 256; keyIndex++) {
    uint8_t key = static_cast<uint8_t>(keyIndex);
    std::vector<uint8_t> xorResult = singleByteXOR(bytes, key);
    int score = letterFrequencyScore(xorResult);
    if (score > maxScore) {
      maxScore = score;
      bestKey = key;
      maxScoreXOR = xorResult;
    }
  }
  return {maxScore, bestKey, maxScoreXOR};
}

// Vigenere's Cipher
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
