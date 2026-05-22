#pragma once

#include <cstdint>
#include <span>
#include <vector>

std::vector<uint8_t> modeEncryptionOracle(std::span<const uint8_t> plaintext);
