#include <bit>
#include <cassert>
#include <cstdint>
#include <optional>
#include <span>
#include <sys/random.h>
#include <vector>

#include "src/lib/utils.hpp"

// XOR
void fixedXOR(std::span<uint8_t> buf1, std::span<const uint8_t> buf2) {
  assert(buf1.size() == buf2.size());
  for (size_t i = 0; i < buf1.size(); ++i) {
    buf1[i] ^= buf2[i];
  }
}

void singleByteXOR(std::span<uint8_t> buffer, uint8_t key) {
  for (size_t i = 0; i < buffer.size(); ++i) {
    buffer[i] ^= key;
  }
}

void repeatingKeyXOR(std::span<uint8_t> buffer, std::span<const uint8_t> key) {
  size_t keyIndex = 0;
  for (size_t i = 0; i < buffer.size(); ++i) {
    buffer[i] ^= key[keyIndex];
    if (++keyIndex == key.size()) {
      keyIndex = 0;
    }
  }
}

// Hamming Distance
std::optional<int> findHammingDist(std::span<const uint8_t> buffer1,
                                   std::span<const uint8_t> buffer2) {
  if (buffer1.size() != buffer2.size()) {
    return std::nullopt;
  }

  int dist = 0;
  for (size_t i = 0; i < buffer1.size(); ++i) {
    dist += std::popcount(static_cast<uint8_t>(buffer1[i] ^ buffer2[i]));
  }
  return dist;
}

// random bytes
std::vector<uint8_t> generateBytes(size_t n) {
  std::vector<uint8_t> bytes(n);
  getrandom(bytes.data(), n, 0);
  return bytes;
}
