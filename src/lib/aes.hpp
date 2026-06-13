#pragma once

#include <cstdint>
#include <span>
#include <vector>

constexpr size_t BLOCK_SIZE = 16;
constexpr int ROUNDS = 10;

std::vector<uint8_t> padPKCS7(std::span<const uint8_t> buffer);

// ECB Mode
void encryptAES_ECB(std::span<uint8_t> buffer,
                    std::span<const uint8_t, BLOCK_SIZE> key);
void decryptAES_ECB(std::span<uint8_t> buffer,
                    std::span<const uint8_t, BLOCK_SIZE> key);

// CBC Mode
void encryptAES_CBC(std::span<uint8_t> buffer,
                    std::span<const uint8_t, BLOCK_SIZE> iv,
                    std::span<const uint8_t, BLOCK_SIZE> key);
void decryptAES_CBC(std::span<uint8_t> buffer,
                    std::span<const uint8_t, BLOCK_SIZE> iv,
                    std::span<const uint8_t, BLOCK_SIZE> key);
