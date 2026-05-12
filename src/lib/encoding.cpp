#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "src/lib/encoding.hpp"

const std::string BASE64_TABLE =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const std::string HEX_TABLE = "0123456789abcdef";

std::optional<uint8_t> fromHex(char c) {
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
  if (hex.size() % 2 != 0) {
    return std::nullopt;
  }
  std::vector<uint8_t> bytes;
  bytes.reserve(hex.size() / 2);

  for (size_t i = 0; i < hex.size(); i += 2) {
    auto high_opt = fromHex(hex[i]);
    auto low_opt = fromHex(hex[i + 1]);

    if (!high_opt || !low_opt) {
      return std::nullopt;
    }
    uint8_t byteValue = (*high_opt << 4) | *low_opt;
    bytes.push_back(byteValue);
  }
  return bytes;
}

std::string bytesToHex(std::span<const uint8_t> bytes) {
  std::string output;
  output.reserve(2 * bytes.size());

  for (size_t i = 0; i < bytes.size(); ++i) {
    output.push_back(HEX_TABLE[bytes[i] >> 4]);
    output.push_back(HEX_TABLE[bytes[i] & 0x0f]);
  }
  return output;
}

std::string bytesToBase64(std::span<const uint8_t> bytes) {
  std::string output;
  output.reserve(((bytes.size() + 2) / 3) * 4);
  size_t i = 0;
  for (; i + 3 <= bytes.size(); i += 3) {
    uint32_t bitstream = (static_cast<uint32_t>(bytes[i]) << 16) |
                         (static_cast<uint32_t>(bytes[i + 1]) << 8) |
                         (static_cast<uint32_t>(bytes[i + 2]));
    output.push_back(BASE64_TABLE[(bitstream >> 18) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 12) & 0x3f]);
    output.push_back(BASE64_TABLE[(bitstream >> 6) & 0x3f]);
    output.push_back(BASE64_TABLE[bitstream & 0x3f]);
  }

  size_t paddingCase = bytes.size() - i;
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
  size_t padding = 0;
  if (base64.size() >= 2) {
    if (base64[base64.size() - 1] == '=')
      ++padding;
    if (base64[base64.size() - 2] == '=')
      ++padding;
  }
  bytes.reserve((base64.size() / 4) * 3 - padding);

  for (size_t i = 0; i < base64.size(); i += 4) {
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

std::string bytesToString(std::span<const uint8_t> bytes) {
  return std::string(bytes.begin(), bytes.end());
}

std::vector<uint8_t> stringToBytes(const std::string &str) {
  return std::vector<uint8_t>(str.begin(), str.end());
}
