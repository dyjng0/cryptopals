#pragma once

#include <cstdint>
#include <optional>
#include <vector>

// XOR
std::optional<std::vector<uint8_t>> fixedXOR(std::vector<uint8_t> &buf1,
                                             const std::vector<uint8_t> &buf2);
void singleByteXOR(std::vector<uint8_t> &buffer, uint8_t key);
void repeatingKeyXOR(std::vector<uint8_t> &buffer,
                     const std::vector<uint8_t> &key);

// Hamming Distance
std::optional<int> findHammingDist(const std::vector<uint8_t> &buffer1,
                                   const std::vector<uint8_t> &buffer2);
