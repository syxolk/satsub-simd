#pragma once

#include <cstdint>

void satsub_naive(std::uint8_t *data, std::size_t len, std::uint8_t y);
void satsub_branchless(std::uint8_t *data, std::size_t len, std::uint8_t y);
void satsub_sse(std::uint8_t *data, std::size_t len, std::uint8_t y);
void satsub_builtin(std::uint8_t *data, std::size_t len, std::uint8_t y);
