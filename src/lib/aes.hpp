#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <span>

constexpr int BLOCK_SIZE = 16;
constexpr int ROUNDS = 10;

// decrypt
void decryptAES(std::span<uint8_t> buffer,
                std::span<const uint8_t, BLOCK_SIZE> key);
