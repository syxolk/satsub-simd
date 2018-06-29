#include <gtest/gtest.h>
#include <cstdint>
#include "satsub.hpp"

constexpr std::size_t SIZE = 18;
constexpr std::uint8_t input[SIZE]{0,1,2,3,4,5,6,7,8,9,255,254,253,252,251,250,249,0};
constexpr std::uint8_t result1[SIZE]{0,0,1,2,3,4,5,6,7,8,254,253,252,251,250,249,248,0};
constexpr std::uint8_t result3[SIZE]{0,0,0,0,1,2,3,4,5,6,252,251,250,249,248,247,246,0};
constexpr std::uint8_t result255[SIZE]{0};

class SatSubTest : public ::testing::TestWithParam<std::uint8_t> {
protected:
    alignas(16) std::uint8_t data[SIZE];

    const std::uint8_t* getExpectedResult(std::uint8_t y) {
        switch(y) {
            case 0: return input;
            case 1: return result1;
            case 3: return result3;
            case 255: return result255;
            default: throw std::invalid_argument("Invalid test parameter");
        }
    }

    virtual void SetUp() {
        memcpy(data, input, SIZE);
    }
};

TEST_P(SatSubTest, naive) {
    satsub_naive(data, SIZE, GetParam());

    const auto expectedResult = getExpectedResult(GetParam());
    for(std::size_t i=0; i<SIZE; i++) {
        EXPECT_EQ(data[i], expectedResult[i]) << "Index " << i;
    }
}

TEST_P(SatSubTest, branchless) {
    satsub_branchless(data, SIZE, GetParam());

    const auto expectedResult = getExpectedResult(GetParam());
    for(std::size_t i=0; i<SIZE; i++) {
        EXPECT_EQ(data[i], expectedResult[i]) << "Index " << i;
    }
}

TEST_P(SatSubTest, sse_aligned) {
    satsub_sse(data, SIZE, GetParam());

    const auto expectedResult = getExpectedResult(GetParam());
    for(std::size_t i=0; i<SIZE; i++) {
        EXPECT_EQ(data[i], expectedResult[i]) << "Index " << i;
    }
}

TEST_P(SatSubTest, builtin) {
    satsub_builtin(data, SIZE, GetParam());

    const auto expectedResult = getExpectedResult(GetParam());
    for(std::size_t i=0; i<SIZE; i++) {
        EXPECT_EQ(data[i], expectedResult[i]) << "Index " << i;
    }
}

INSTANTIATE_TEST_CASE_P(SimpleValues, SatSubTest, ::testing::Values(0, 1, 3, 255));

TEST(Satsub, SSE_BadAlignment) {
    std::uint8_t data[SIZE];
    for(auto o=0; o<16; o++) {
        memcpy(data, input, SIZE);

        if(o>0) {
            satsub_naive(data, o, 1);
        }
        satsub_sse(&data[o], SIZE-o, 1);

        for(std::size_t i=0; i<SIZE; i++) {
            EXPECT_EQ(data[i], result1[i]) << "Offset " << o << " Index " << i;
        }
    }
}
