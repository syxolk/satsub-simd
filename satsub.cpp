#include "satsub.hpp"

#include <immintrin.h>

void satsub_naive(std::uint8_t *data, std::size_t len, std::uint8_t y) {
    for (std::size_t i = 0; i < len; i++) {
        if (data[i] >= y) {
            data[i] -= y;
        } else {
            data[i] = 0;
        }
    }
}

void satsub_branchless(std::uint8_t *data, std::size_t len, std::uint8_t y) {
    for (std::size_t i = 0; i < len; i++) {
        // https://stackoverflow.com/a/33482123
        std::uint8_t x = data[i];
        std::uint8_t res = x - y;
        res &= -(res <= x);
        data[i] = res;
    }
}

void satsub_sse(std::uint8_t *data, std::size_t len, std::uint8_t y) {
    // https://stackoverflow.com/a/1898156
    // https://stackoverflow.com/a/11298461
    std::size_t offset = 16 - (reinterpret_cast<std::uintptr_t>(data) % 16);
    if (offset > 0) {
        satsub_branchless(data, offset, y);
    }

    std::size_t i = offset;

    const auto y_vec = _mm_set1_epi8(y);
    const std::size_t cnt = (len - offset) / 16;
    for (std::size_t j = 0; j < cnt; j++) {
        const auto x = _mm_load_si128(reinterpret_cast<__m128i *>(&data[i]));
        const auto result = _mm_subs_epu8(x, y_vec);
        _mm_store_si128(reinterpret_cast<__m128i *>(&data[i]), result);
        i += 16;
    }

    satsub_branchless(&data[i], len - i, y);
}

void satsub_builtin(std::uint8_t *data, std::size_t len, std::uint8_t y) {
    for (std::size_t i = 0; i < len; i++) {
        auto x = data[i];
        bool no_overflow = !__builtin_sub_overflow(x, y, &x);
        x &= -no_overflow;
        data[i] = x;
    }
}
