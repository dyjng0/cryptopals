#include <cstdint>
#include <optional>
#include <vector>

#include "src/lib/xor.hpp"

std::optional<std::vector<uint8_t>> fixedXOR(const std::vector<uint8_t> &buf1,
                                             const std::vector<uint8_t> &buf2) {
  if (buf1.size() != buf2.size()) {
    return std::nullopt;
  }
  std::vector<uint8_t> output;
  output.reserve(buf1.size());
  for (size_t i = 0; i < buf1.size(); i++) {
    output.push_back(buf1[i] ^ buf2[i]);
  }
  return output;
}

std::vector<uint8_t> singleByteXOR(const std::vector<uint8_t> &buffer,
                                   uint8_t key) {
  const size_t len = buffer.size();
  std::vector<uint8_t> output;
  output.reserve(len);
  for (size_t i = 0; i < len; i++) {
    output.push_back(key ^ buffer[i]);
  }
  return output;
}

std::vector<uint8_t> repeatingKeyXOR(const std::vector<uint8_t> &buffer,
                                     const std::vector<uint8_t> &key) {
  const size_t bufferLen = buffer.size();
  const size_t keyLen = key.size();
  std::vector<uint8_t> output;
  output.reserve(bufferLen);
  for (size_t i = 0; i < bufferLen; i++) {
    output.push_back(buffer[i] ^ key[i % keyLen]);
  }
  return output;
}
