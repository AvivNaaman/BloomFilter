// Murmur Hash 3 implementation by https://github.com/PeterScott/murmur3
//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the
// public domain. The author hereby disclaims copyright to this source
// code.

#ifndef _MURMURHASH_H_
#define _MURMURHASH_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

void MurmurHash3_x86_32 (const void *key, int len, uint32_t seed, void *out);

void MurmurHash3_x86_128(const void *key, int len, uint32_t seed, void *out);

void MurmurHash3_x64_128(const void *key, int len, uint32_t seed, void *out);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // _MURMURHASH_H_
