#pragma once

#include <cstdint>
#include <optional>
#include <span>

std::optional<int> getLetterIndex(const uint8_t byte);
int letterFrequencyScore(std::span<const uint8_t> bytes);
