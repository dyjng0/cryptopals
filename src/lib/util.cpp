#include <cstdint>
#include <optional>
#include <vector>

#include "src/lib/util.hpp"

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

std::optional<double> avgHammingDist(const std::vector<uint8_t> &buffer,
                                     int keySize) {
  if (static_cast<size_t>(2 * keySize) > buffer.size()) {
    return std::nullopt;
  }

  int blocks = std::min(buffer.size() / keySize, static_cast<size_t>(4));
  int totalDist = 0;
  for (int i = 0; i < blocks - 1; i++) {
    std::vector<uint8_t> buffer1(buffer.begin() + i * keySize,
                                 buffer.begin() + (i + 1) * keySize);
    for (int j = i; j < blocks; j++) {
      std::vector<uint8_t> buffer2(buffer.begin() + j * keySize,
                                   buffer.begin() + (j + 1) * keySize);
      auto dist = findHammingDist(buffer1, buffer2);
      if (!dist) {
        continue;
      }
      totalDist += *dist;
    }
  }
  int iterations = (blocks * (blocks - 1)) / 2;
  return static_cast<double>(totalDist) / iterations;
}
