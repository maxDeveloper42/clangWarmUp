/**
 * @file memcpy.c
 * @brief Implementation of my_memcpy with optional optimisation.
 */

#include "memcpy.h"
#include <stdint.h>   /* uintptr_t */

/* The macro CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE may be defined
 * externally (e.g., via -D compiler flag). If not defined, the word‑copy
 * path is included. */

/* Use the machine's word size – on Linux this is typically the pointer size. */
typedef unsigned long word_t;

void *my_memcpy(void *restrict d, const void *restrict s, size_t n)
{
    unsigned char *d_byte = (unsigned char *)d;
    const unsigned char *s_byte = (const unsigned char *)s;

#if !defined(CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE)
    const uintptr_t mask = sizeof(word_t) - 1;

    /* Attempt word‑aligned copies only if buffers have identical alignment. */
    if ((((uintptr_t)d ^ (uintptr_t)s_byte) & mask) == 0) {

        /* Byte‑copy until destination is word‑aligned (or n == 0). */
        while (((uintptr_t)d_byte) & mask) {
            if (n == 0) {
                return d;
            }
            *(d_byte++) = *(s_byte++);
            n--;
        }

        /* Word‑copy as many full words as possible. */
        word_t *d_word = (word_t *)d_byte;
        const word_t *s_word = (const word_t *)s_byte;

        while (n >= sizeof(word_t)) {
            *(d_word++) = *(s_word++);
            n -= sizeof(word_t);
        }

        d_byte = (unsigned char *)d_word;
        s_byte = (unsigned char *)s_word;
    }
#endif

    /* Finish any remaining bytes (tail). */
    while (n > 0) {
        *(d_byte++) = *(s_byte++);
        n--;
    }

    return d;
}
