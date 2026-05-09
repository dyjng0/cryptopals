#pragma once

#include <cstdint>
#include <optional>
#include <vector>

std::optional<int> getLetterIndex(const uint8_t byte);
int letterFrequencyScore(const std::vector<uint8_t> &bytes);
