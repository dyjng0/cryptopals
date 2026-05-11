#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

std::optional<uint8_t> fromHex(char c);
std::optional<uint8_t> fromBase64(char c);
std::optional<std::vector<uint8_t>> hexToBytes(const std::string &hex);
std::string bytesToHex(std::span<const uint8_t> bytes);
std::string bytesToBase64(std::span<const uint8_t> bytes);
std::optional<std::vector<uint8_t>> base64ToBytes(const std::string &base64);
std::string bytesToString(std::span<const uint8_t> bytes);
std::vector<uint8_t> stringToBytes(const std::string &str);
