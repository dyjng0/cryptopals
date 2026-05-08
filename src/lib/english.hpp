#pragma once

#include <cstdint>
#include <optional>
#include <vector>

struct MaxScoreResults {
  int maxScore;
  uint8_t bestKey;
  std::vector<uint8_t> maxScoreXOR;
};

std::optional<int> getLetterIndex(const uint8_t byte);
int letterFrequencyScore(const std::vector<uint8_t> &bytes);
MaxScoreResults testKeys(const std::vector<uint8_t> &bytes);
