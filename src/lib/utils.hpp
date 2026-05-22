#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <vector>

// XOR
void fixedXOR(std::span<uint8_t> buf1, std::span<const uint8_t> buf2);
void singleByteXOR(std::span<uint8_t> buffer, uint8_t key);
void repeatingKeyXOR(std::span<uint8_t> buffer, std::span<const uint8_t> key);

// Hamming Distance
std::optional<int> findHammingDist(std::span<const uint8_t> buffer1,
                                   std::span<const uint8_t> buffer2);

// random bytes
std::vector<uint8_t> generateBytes(size_t n);
template <size_t N> std::array<uint8_t, N> generateBytes();
