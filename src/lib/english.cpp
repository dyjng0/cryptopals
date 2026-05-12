#include <cmath>
#include <cstdint>
#include <optional>
#include <span>

#include "src/lib/english.hpp"

static constexpr std::array<int, 26> LETTER_FREQUENCY = {
    855, 160, 316, 387, 1210, 218, 209, 496, 733, 22,  81, 421, 253,
    717, 747, 207, 10,  633,  673, 894, 268, 106, 183, 19, 172, 11};
static constexpr int SPACE_SCORE = 1300;
static constexpr int NON_PRINTABLE_PENALTY = -5000;

std::optional<int> getLetterIndex(const uint8_t byte) {
  if (byte >= 'a' && byte <= 'z') {
    return static_cast<int>(byte - 'a');
  } else if (byte >= 'A' && byte <= 'Z') {
    return static_cast<int>(byte - 'A');
  }
  return std::nullopt;
}

int letterFrequencyScore(std::span<const uint8_t> bytes) {
  int score = 0;
  for (uint8_t byte : bytes) {
    auto letterIndex = getLetterIndex(byte);
    if (letterIndex) {
      score += LETTER_FREQUENCY[*letterIndex];
    } else if (byte == ' ') {
      score += SPACE_SCORE;
    } else if (byte < 32 || byte > 126) {
      score += NON_PRINTABLE_PENALTY;
    }
  }
  return score;
}
