#include <bit>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <sys/types.h>
#include <vector>

#include "src/lib/encoding.hpp"

const std::string BASE64_TABLE =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const std::string HEX_TABLE = "0123456789abcdef";

std::optional<uint8_t> toHex(char c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'a' && c <= 'f') {
    return 10 + (c - 'a');
  } else if (c >= 'A' && c <= 'F') {
    return 10 + (c - 'A');
  } else {
    return std::nullopt;
  }
}

std::optional<uint8_t> fromBase64(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A';
  } else if (c >= 'a' && c <= 'z') {
    return c - 'a' + 26;
  } else if (c >= '0' && c <= '9') {
    return c - '0' + 52;
  } else if (c == '+') {
    return 62;
  } else if (c == '/') {
    return 63;
  } else if (c == '=') {
    return 0;
  } else {
    return std::nullopt;
  }
}

std::optional<std::vector<uint8_t>> hexToBytes(const std::string &hex) {
  const int len = hex.length();
  if (len % 2 != 0) {
    return std::nullopt;
  }
  std::vector<uint8_t> bytes;
  bytes.reserve(len / 2);

  for (int i = 0; i < len; i += 2) {
    auto high_opt = toHex(hex[i]);
    auto low_opt = toHex(hex[i + 1]);

    if (!high_opt || !low_opt) {
      return std::nullopt;
    }
    uint8_t byteValue = (*high_opt << 4) | *low_opt;
    bytes.push_back(byteValue);
  }
  return bytes;
}

std::string bytesToHex(const std::vector<uint8_t> &bytes) {
  const size_t len = bytes.size();
  std::string output;
  output.reserve(2 * len);

  for (size_t i = 0; i < len; i++) {
    output.push_back(HEX_TABLE[bytes[i] >> 4]);
    output.push_back(HEX_TABLE[bytes[i] & 0x0f]);
  }
  return output;
}

std::string bytesToBase64(const std::vector<uint8_t> &bytes) {
  const size_t len = bytes.size();
  std::string output;
  output.reserve(((len + 2) / 3) * 4);
  size_t i = 0;
  for (; i + 3 <= len; i += 3) {
    uint32_t bitstream = (static_cast<uint32_t>(bytes[i]) << 16) |
                         (static_cast<uint32_t>(bytes[i + 1]) << 8) |
                         (static_cast<uint32_t>(bytes[i + 2]));
    output.push_back(BASE64_TABLE[(bitstream >> 18) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 12) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 6) & 0x3f]);
    output.push_back(BASE64_TABLE[bitstream & 0x3f]);
  }

  size_t paddingCase = len - i;
  if (paddingCase == 1) {
    uint32_t bitstream = static_cast<uint32_t>(bytes[i]) << 16;
    output.push_back(BASE64_TABLE[(bitstream >> 18) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 12) & 0x3f]);
    output.push_back('=');
    output.push_back('=');
  } else if (paddingCase == 2) {
    uint32_t bitstream = (static_cast<uint32_t>(bytes[i]) << 16) |
                         (static_cast<uint32_t>(bytes[i + 1]) << 8);
    output.push_back(BASE64_TABLE[(bitstream >> 18) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 12) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 6) & 0x3f]);
    output.push_back('=');
  }
  return output;
}

std::optional<std::vector<uint8_t>> base64ToBytes(const std::string &base64) {
  if (base64.empty() || base64.size() % 4 != 0) {
    return std::nullopt;
  }

  std::vector<uint8_t> bytes;
  const size_t len = base64.size();
  size_t padding = 0;
  if (len >= 2) {
    if (base64[len - 1] == '=')
      padding++;
    if (base64[len - 2] == '=')
      padding++;
  }
  bytes.reserve((len / 4) * 3 - padding);

  for (size_t i = 0; i < len; i += 4) {
    auto c1 = fromBase64(base64[i]);
    auto c2 = fromBase64(base64[i + 1]);
    auto c3 = fromBase64(base64[i + 2]);
    auto c4 = fromBase64(base64[i + 3]);
    if (!c1 || !c2 || !c3 || !c4) {
      return std::nullopt;
    }

    uint32_t bitstream =
        (static_cast<uint32_t>(*c1) << 18) | (static_cast<uint32_t>(*c2) << 12);
    bytes.push_back(static_cast<uint8_t>(bitstream >> 16));

    if (base64[i + 2] != '=') {
      bitstream |= (static_cast<uint32_t>(*c3) << 6);
      bytes.push_back(static_cast<uint8_t>((bitstream >> 8) & 0xff));
      if (base64[i + 3] != '=') {
        bitstream |= static_cast<uint32_t>(*c4);
        bytes.push_back(static_cast<uint8_t>(bitstream & 0xff));
      }
    }
  }
  return bytes;
}

std::string bytesToString(const std::vector<uint8_t> &bytes) {
  return std::string(bytes.begin(), bytes.end());
}

std::vector<uint8_t> stringToBytes(const std::string &str) {
  return std::vector<uint8_t>(str.begin(), str.end());
}

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
