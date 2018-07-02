#include <cpuid.h>
#include <cstdint>
#include <cstdio>
#include <immintrin.h>

void cpuid(int info[4], int infoType) {
    __cpuid_count(infoType, 0, info[0], info[1], info[2], info[3]);
}

const char *boolToString(bool x) { return x ? "yes" : "no"; }

int main() {
    int info[4];
    cpuid(info, 0);
    int nIds = info[0];

    bool HW_SSE = false;
    bool HW_SSE2 = false;
    bool HW_SSE3 = false;
    bool HW_SSE41 = false;
    bool HW_SSE42 = false;
    bool HW_AVX = false;
    bool HW_AVX2 = false;

    if (nIds >= 0x00000001) {
        cpuid(info, 0x00000001);
        HW_SSE = (info[3] & ((int)1 << 25)) != 0;
        HW_SSE2 = (info[3] & ((int)1 << 26)) != 0;
        HW_SSE3 = (info[2] & ((int)1 << 0)) != 0;
        HW_SSE41 = (info[2] & ((int)1 << 19)) != 0;
        HW_SSE42 = (info[2] & ((int)1 << 20)) != 0;
        HW_AVX = (info[2] & ((int)1 << 28)) != 0;
    }
    if (nIds >= 0x00000007) {
        cpuid(info, 0x00000007);
        HW_AVX2 = (info[1] & ((int)1 << 5)) != 0;
    }

    printf("Supports SSE:    %s\n", boolToString(HW_SSE));
    printf("Supports SSE2:   %s\n", boolToString(HW_SSE2));
    printf("Supports SSE3:   %s\n", boolToString(HW_SSE3));
    printf("Supports SSE4.1: %s\n", boolToString(HW_SSE41));
    printf("Supports SSE4.2: %s\n", boolToString(HW_SSE42));
    printf("Supports AVX:    %s\n", boolToString(HW_AVX));
    printf("Supports AVX2:   %s\n", boolToString(HW_AVX2));
}
