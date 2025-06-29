#ifndef CPUDETECT_H
#define CPUDETECT_H

enum SIMD_ISA
{
    NOSIMD = 0,
    SSSE3,
    AVX2,
    AVX512,
    NEON,
    SVE
};

static int inline count_trailing_zeros(unsigned long long resmask)
{
#ifndef _WIN32
    int offset = __builtin_ctzll(resmask);
#elif defined(_BitScanForward64)
    unsigned long offset = 0;
    const unsigned char dummyIsNonZero =_BitScanForward64(&offset, resmask); // resmask can't be 0 in this if
#else // Fallback to the slow method.
    int offset = 0;
    while (!(resmask & 1)) {
        resmask >>= 1;
        offset++;
    }
#endif
    return offset;
}

SIMD_ISA check_simd_support();

#endif