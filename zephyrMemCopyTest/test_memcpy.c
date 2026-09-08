/**
 * @file test_memcpy.c
 * @brief Test harness for my_memcpy.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memcpy.h"

/* ------------------------------------------------------------------
 * Helper to run a single test with aligned and unaligned destination.
 * ------------------------------------------------------------------ */
static void run_test(const char *src, size_t len, const char *desc)
{
    printf("%s\n", desc);

    unsigned char *dst_raw = malloc(len + 16);
    if (!dst_raw) {
        fprintf(stderr, "  malloc failed\n");
        return;
    }

    /* Aligned destination (offset 0) */
    unsigned char *dst_aligned = dst_raw;
    my_memcpy(dst_aligned, src, len);
    if (memcmp(dst_aligned, src, len) == 0) {
        printf("  [PASS] aligned copy\n");
    } else {
        printf("  [FAIL] aligned copy\n");
    }

    /* Unaligned destination (offset 1) */
    unsigned char *dst_unaligned = dst_raw + 1;
    my_memcpy(dst_unaligned, src, len);
    if (memcmp(dst_unaligned, src, len) == 0) {
        printf("  [PASS] unaligned copy (offset 1)\n");
    } else {
        printf("  [FAIL] unaligned copy (offset 1)\n");
    }

    free(dst_raw);
}

/* ------------------------------------------------------------------
 * Main test sequence.
 * ------------------------------------------------------------------ */
int main(void)
{
    printf("===== Testing my_memcpy =====\n");
#if defined(CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE)
    printf("Optimisation: SIZE (byte‑only loop)\n\n");
#else
    printf("Optimisation: SPEED (word‑aligned loop)\n\n");
#endif

    /* Test 1: short string (including NUL) */
    run_test("Hello", sizeof("Hello"), "Test 1: short string");

    /* Test 2: medium string (spans several words) */
    run_test("The quick brown fox jumps over the lazy dog. "
             "This is long enough to trigger word copying if enabled.",
             sizeof("The quick brown fox jumps over the lazy dog. "
                    "This is long enough to trigger word copying if enabled."),
             "Test 2: medium string");

    /* Test 3: large buffer (1 KB) */
    char *large_src = malloc(1024);
    if (large_src) {
        for (int i = 0; i < 1023; i++)
            large_src[i] = 'A' + (i % 26);
        large_src[1023] = '\0';
        run_test(large_src, 1024, "Test 3: 1 KB buffer");
        free(large_src);
    } else {
        fprintf(stderr, "  large_src malloc failed\n");
    }

    /* Test 4: zero length */
    printf("Test 4: zero‑byte copy\n");
    unsigned char zero_dst[10] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE,
                                   0xFF, 0x11, 0x22, 0x33, 0x44};
    my_memcpy(zero_dst, "dummy", 0);
    if (zero_dst[0] == 0xAA && zero_dst[1] == 0xBB) {
        printf("  [PASS] destination unchanged\n");
    } else {
        printf("  [FAIL] destination modified\n");
    }

    /* Test 5: overlapping? Not required (we trust caller), but we can test
     * copying backward? This implementation is for non‑overlapping buffers,
     * so we don't test that. */

    printf("\nAll tests done.\n");
    return 0;
}
