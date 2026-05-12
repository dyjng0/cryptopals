#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <span>

static constexpr int BLOCK_SIZE = 16;
static constexpr int ROUNDS = 10;

// helpers
void addRoundKey(std::span<uint8_t, BLOCK_SIZE> block,
                 std::span<const uint8_t, BLOCK_SIZE> roundKey);
void invShiftRows(std::span<uint8_t, BLOCK_SIZE> block);
void invSubBytes(std::span<uint8_t, BLOCK_SIZE> block);
void invMixColumns(std::span<uint8_t, BLOCK_SIZE> block);

// key sched
std::array<std::array<uint8_t, BLOCK_SIZE>, ROUNDS + 1>
expandKey(std::span<const uint8_t, BLOCK_SIZE> key);

// decrypt
void decryptAES(std::span<uint8_t> buffer,
                std::span<const uint8_t, BLOCK_SIZE> key);
