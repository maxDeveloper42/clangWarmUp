/**
 * @file memcpy.h
 * @brief Custom memcpy implementation with optional size/speed trade‑off.
 */

#ifndef MEMCPY_H
#define MEMCPY_H

#include <stddef.h>   /* size_t */

/**
 * @brief Copy memory area (drop-in replacement for standard memcpy).
 *
 * @param d         Destination buffer.
 * @param s         Source buffer.
 * @param n         Number of bytes to copy.
 * @return          Pointer to destination.
 *
 * @note The implementation may use word‑aligned copies if the macro
 *       CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE is NOT defined.
 *       If that macro is defined, only byte‑by‑byte copying is used.
 */
void *my_memcpy(void *restrict d, const void *restrict s, size_t n);

#endif /* MEMCPY_H */
