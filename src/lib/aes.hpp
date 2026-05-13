#pragma once

#include <cstdint>
#include <span>
#include <vector>

constexpr int BLOCK_SIZE = 16;
constexpr int ROUNDS = 10;

std::vector<uint8_t> padPKCS7(std::span<const uint8_t> buffer);

// decrypt
void decryptAES(std::span<uint8_t> buffer,
                std::span<const uint8_t, BLOCK_SIZE> key);
