#pragma once

#include <cstdint>
#include <optional>
#include <vector>

// XOR
std::optional<std::vector<uint8_t>> fixedXOR(const std::vector<uint8_t> &buf1,
                                             const std::vector<uint8_t> &buf2);
std::vector<uint8_t> singleByteXOR(const std::vector<uint8_t> &buffer,
                                   uint8_t key);
std::vector<uint8_t> repeatingKeyXOR(const std::vector<uint8_t> &buffer,
                                     const std::vector<uint8_t> &key);

// Hamming Distance
std::optional<int> findHammingDist(const std::vector<uint8_t> &buffer1,
                                   const std::vector<uint8_t> &buffer2);
