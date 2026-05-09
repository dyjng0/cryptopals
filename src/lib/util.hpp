#pragma once

#include <cstdint>
#include <optional>
#include <vector>

std::optional<int> findHammingDist(const std::vector<uint8_t> &buffer1,
                                   const std::vector<uint8_t> &buffer2);
std::optional<double> avgHammingDist(const std::vector<uint8_t> &buffer,
                                     int keySize);
