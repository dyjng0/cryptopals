#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

std::optional<uint8_t> toHex(char c);
std::optional<std::vector<uint8_t>> hexToBytes(const std::string &hex);
std::string bytesToHex(const std::vector<uint8_t> &bytes);
std::string bytesToBase64(const std::vector<uint8_t> &bytes);
std::string bytesToString(const std::vector<uint8_t> &bytes);
std::vector<uint8_t> stringToBytes(const std::string &str);

std::optional<std::vector<uint8_t>> fixedXOR(const std::vector<uint8_t> &buf1,
                                             const std::vector<uint8_t> &buf2);
std::vector<uint8_t> singleByteXOR(const std::vector<uint8_t> &buffer,
                                   uint8_t key);
std::vector<uint8_t> repeatingKeyXOR(const std::vector<uint8_t> &buffer,
                                     const std::vector<uint8_t> &key);
