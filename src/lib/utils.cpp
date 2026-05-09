#include <bit>
#include <cstdint>
#include <optional>
#include <vector>

#include "src/lib/utils.hpp"

// XOR
std::optional<std::vector<uint8_t>> fixedXOR(std::vector<uint8_t> &buf1,
                                             const std::vector<uint8_t> &buf2) {
  if (buf1.size() != buf2.size()) {
    return std::nullopt;
  }
  for (size_t i = 0; i < buf1.size(); i++) {
    buf1[i] ^= buf2[i];
  }
  return buf1;
}

void singleByteXOR(std::vector<uint8_t> &buffer, uint8_t key) {
  for (size_t i = 0; i < buffer.size(); i++) {
    buffer[i] ^= key;
  }
}

void repeatingKeyXOR(std::vector<uint8_t> &buffer,
                     const std::vector<uint8_t> &key) {
  size_t keyIndex = 0;
  for (size_t i = 0; i < buffer.size(); i++) {
    buffer[i] ^= key[keyIndex];
    if (++keyIndex == key.size()) {
      keyIndex = 0;
    }
  }
}

// Hamming Distance
std::optional<int> findHammingDist(const std::vector<uint8_t> &buffer1,
                                   const std::vector<uint8_t> &buffer2) {
  if (buffer1.size() != buffer2.size()) {
    return std::nullopt;
  }

  int dist = 0;
  for (size_t i = 0; i < buffer1.size(); i++) {
    dist += std::popcount(static_cast<uint8_t>(buffer1[i] ^ buffer2[i]));
  }
  return dist;
}
