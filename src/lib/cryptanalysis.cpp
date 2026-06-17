#include <algorithm>
#include <cassert>
#include <cstdint>
#include <optional>
#include <span>
#include <unordered_set>
#include <vector>

#include "src/lib/aes.hpp"
#include "src/lib/cryptanalysis.hpp"
#include "src/lib/english.hpp"
#include "src/lib/utils.hpp"

// Single-byte XOR
MaxScoreResults breakSingleByteXOR(std::span<const uint8_t> bytes) {
  int bestScore = -1;
  uint8_t bestKey = 0;
  std::vector<uint8_t> bestCandidate;
  for (int keyIndex = 0; keyIndex < 256; ++keyIndex) {
    uint8_t key = static_cast<uint8_t>(keyIndex);
    std::vector<uint8_t> candidate(bytes.begin(), bytes.end());
    singleByteXOR(candidate, key);
    int score = letterFrequencyScore(candidate);
    if (score > bestScore) {
      bestScore = score;
      bestKey = key;
      bestCandidate = std::move(candidate);
    }
  }
  return {bestScore, bestKey, bestCandidate};
}

// Vigenere's Cipher
double avgHammingDist(std::span<const uint8_t> buffer, size_t keySize) {
  assert(2 * keySize <= buffer.size());

  size_t blocks = std::min(buffer.size() / keySize, static_cast<size_t>(4));
  int totalDist = 0;
  for (size_t i = 0; i < blocks - 1; ++i) {
    auto span1 = std::span(buffer).subspan(i * keySize, keySize);
    for (size_t j = i + 1; j < blocks; ++j) {
      auto span2 = std::span(buffer).subspan(j * keySize, keySize);
      auto dist = findHammingDist(span1, span2);
      if (dist) {
        totalDist += *dist;
      }
    }
  }
  size_t iterations = (blocks * (blocks - 1)) / 2;
  return static_cast<double>(totalDist) / iterations;
}

size_t findKeySize(std::span<const uint8_t> buffer) {
  double smallestDist = static_cast<double>(buffer.size()) / 2 * 8;
  size_t keySize = 0;
  for (size_t i = 2; i < buffer.size() / 2 && i < 40; ++i) {
    double dist = avgHammingDist(buffer, i);
    double normalizedDist = dist / i;
    if (normalizedDist < smallestDist) {
      smallestDist = normalizedDist;
      keySize = i;
    }
  }
  return keySize;
}

std::vector<uint8_t> breakVigenere(std::span<const uint8_t> buffer,
                                   size_t keySize) {
  std::vector<uint8_t> key;
  key.reserve(keySize);
  size_t blocks = buffer.size() / keySize;
  for (size_t i = 0; i < keySize; ++i) {
    std::vector<uint8_t> transposed;
    for (size_t blockNum = 0; blockNum < blocks; ++blockNum) {
      transposed.push_back(buffer[blockNum * keySize + i]);
    }
    auto [bestScore, bestKey, bestCandidate] = breakSingleByteXOR(transposed);
    key.push_back(bestKey);
  }
  return key;
}

// Block cipher modes of operation
// Hash functions for span
struct SpanHash {
  size_t operator()(std::span<const uint8_t> bytes) const {
    size_t hash = 0;
    std::hash<uint8_t> hasher;
    for (uint8_t byte : bytes) {
      hash ^= hasher(byte);
    }
    return hash;
  }
};

struct SpanEqual {
  bool operator()(std::span<const uint8_t> a,
                  std::span<const uint8_t> b) const {
    return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin());
  }
};

// Block Cipher Functions
int getECBScore(std::span<const uint8_t> buffer) {
  assert(buffer.size() % BLOCK_SIZE == 0);
  int repeatedBlocks = 0;
  std::unordered_set<std::span<const uint8_t, BLOCK_SIZE>, SpanHash, SpanEqual>
      s;
  for (size_t i = 0; i < buffer.size(); i += BLOCK_SIZE) {
    std::span<const uint8_t, BLOCK_SIZE> block(buffer.begin() + i, BLOCK_SIZE);
    auto [it, inserted] = s.insert(block);
    if (!inserted) {
      ++repeatedBlocks;
    }
  }
  return repeatedBlocks;
}

bool isECB(std::span<const uint8_t> ciphertext) {
  if (getECBScore(ciphertext) > 0) {
    return true;
  }
  return false;
}

size_t findBlockSize(ecbOracle oracle) {
  std::vector<uint8_t> padding(32);
  size_t len = oracle(padding).size();
  padding.push_back('A');
  size_t paddedLen = oracle(padding).size();
  while (len == paddedLen) {
    padding.push_back('A');
    paddedLen = oracle(padding).size();
  }
  return paddedLen - len;
}

std::optional<uint8_t> decryptByteAtIndex(ecbOracle oracle, size_t blockSize,
                                          size_t index,
                                          std::span<const uint8_t> firstBytes) {
  size_t blockIndex = index / blockSize;
  size_t padSize = (blockSize - 1) - (index % blockSize);
  std::vector<uint8_t> input(blockSize, 'A');

  // True byte block
  std::vector<uint8_t> ciphertext =
    oracle(std::vector<uint8_t>(input.begin(), input.begin() + padSize));
std::vector<uint8_t> trueBlock(
    ciphertext.begin() + blockSize * blockIndex,
    ciphertext.begin() + blockSize * blockIndex + blockSize);

  // Set first bytes of input vector
  if (firstBytes.size() > padSize) {
    std::copy(firstBytes.end() - padSize, firstBytes.end(), input.begin());
  } else {
    std::copy(firstBytes.begin(), firstBytes.end(),
              input.begin() + (padSize - firstBytes.size()));
  }

  // Test all possible bytes
  std::span<uint8_t> guessBlock;
  SpanEqual equals;
  for (int byteIndex = 0; byteIndex < 256; ++byteIndex) {
    uint8_t byte = static_cast<uint8_t>(byteIndex);
    input[blockSize - 1] = byte;
    ciphertext = oracle(input);
    guessBlock = std::span(ciphertext).subspan(0, blockSize);
    if (equals(guessBlock, trueBlock)) {
      return byte;
    }
  }
  return std::nullopt;
}
