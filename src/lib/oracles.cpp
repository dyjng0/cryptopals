#include <cstdint>
#include <random>
#include <span>
#include <string>
#include <vector>

#include "src/lib/aes.hpp"
#include "src/lib/encoding.hpp"
#include "src/lib/utils.hpp"

// Detect Mode Oracle
static std::random_device rd;
static std::mt19937 rng{rd()};
static std::uniform_int_distribution<size_t> affixDist{5, 10};
static std::uniform_int_distribution<size_t> modeDist{0, 1};
std::vector<uint8_t> modeEncryptionOracle(std::span<const uint8_t> plaintext) {
  std::vector<uint8_t> key = generateBytes(BLOCK_SIZE);
  size_t prefixLen = affixDist(rng);
  size_t suffixLen = affixDist(rng);
  std::vector<uint8_t> padded;
  padded.reserve(prefixLen + plaintext.size() + suffixLen + BLOCK_SIZE);
  std::vector<uint8_t> prefix = generateBytes(prefixLen);
  std::vector<uint8_t> suffix = generateBytes(suffixLen);
  padded.insert(padded.end(), prefix.begin(), prefix.end());
  padded.insert(padded.end(), plaintext.begin(), plaintext.end());
  padded.insert(padded.end(), suffix.begin(), suffix.end());
  padded = padPKCS7(padded);
  if (modeDist(rng) == 0) {
    encryptAES_ECB(padded,
                   std::span<uint8_t, BLOCK_SIZE>(key.data(), BLOCK_SIZE));
  } else {
    std::vector<uint8_t> iv = generateBytes(BLOCK_SIZE);
    encryptAES_CBC(padded,
                   std::span<uint8_t, BLOCK_SIZE>(iv.data(), BLOCK_SIZE),
                   std::span<uint8_t, BLOCK_SIZE>(key.data(), BLOCK_SIZE));
  }
  return padded;
}

// ECB Encryption Oracle
std::string UNKOWN =
    "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYm"
    "xvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91"
    "IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK";
const std::vector<uint8_t> unknownBytes = *base64ToBytes(UNKOWN);
static std::vector<uint8_t> ecbKey = generateBytes(BLOCK_SIZE);
std::vector<uint8_t> ecbEncryptionOracle(std::span<const uint8_t> plaintext) {
  std::vector<uint8_t> padded;
  padded.reserve(plaintext.size() + unknownBytes.size());
  padded.insert(padded.end(), plaintext.begin(), plaintext.end());
  padded.insert(padded.end(), unknownBytes.begin(), unknownBytes.end());
  padded = padPKCS7(padded);
  encryptAES_ECB(padded,
                 std::span<uint8_t, BLOCK_SIZE>(ecbKey.data(), BLOCK_SIZE));
  return padded;
}
