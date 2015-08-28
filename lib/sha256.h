/* sha256.h - TinyCrypt interface to a SHA-256 implementation. */

/*
 *  Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *    - Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *    - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    - Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  sha256.h -- Interface to a SHA-256 implementation.
 *
 *  Overview:   SHA-256 is a NIST approved cryptographic hashing algorithm
 *              specified in FIPS 180. A hash algorithm maps data of arbitrary
 *              size to data of fixed length.
 *
 *  Security:   SHA-256 provides 128 bits of security against collision attacks
 *              and 256 bits of security against pre-image attacks. SHA-256 does
 *              NOT behave like a random oracle, but it can be used as one if
 *              the string being hashed is prefix-free encoded before hashing.
 *
 *  Usage:      1) call sha256_init to initialize a struct sha256_state_struct
 *              before hashing a new string.
 *
 *              2) call sha256_update to hash the next string segment;
 *              sha256_update can be called as many times as needed to hash
 *              all of the segments of a string; the order is important.
 *
 *              3) call sha256_final to out put the digest from a hashing
 *              operation.
 */

#ifndef __SHA256_H__
#define __SHA256_H__

#include <stddef.h>
#include <stdint.h>

#define SHA256_BLOCK_SIZE (64)
#define SHA256_DIGEST_SIZE (32)
#define SHA256_STATE_BLOCKS (SHA256_DIGEST_SIZE/4)

struct sha256_state_struct {
  uint32_t iv[SHA256_STATE_BLOCKS];
  uint64_t bits_hashed;
  uint8_t leftover[SHA256_BLOCK_SIZE];
  size_t leftover_offset;
};

typedef struct sha256_state_struct *Sha256State_t;

/*
 *  SHA256 initialization procedure.
 *
 *  Effects:    Initializes s and returns 1
 *
 *  Exceptions: Returns 0 if:
 *                s == NULL.
 */
int32_t sha256_init (Sha256State_t s);

/*
 *  SHA256 update procedure.
 *
 *  Assumes:    s has been initialized by sha256_init
 *
 *  Effects:    Hashes data_length bytes addressed by data into state s and
 *              returns 1
 *
 *  Exceptions: Returns 0 if:
 *                s == NULL,
 *                s->iv == NULL,
 *                data == NULL.
 *
 *  Note:       The state buffer 'leftover' is left in memory after processing.
 *              If your application intends to have sensitive data in this
 *              buffer, remind to erase it after the data has been processed.
 */
int32_t sha256_update (Sha256State_t s, const uint8_t *data, size_t datalen);

/*
 *  SHA256 final procedure.
 *
 *  Assumes:    s has been initialized by sha256_init
 *              digest points to at least SHA256_DIGEST_SIZE bytes
 *
 *  Effects:    Inserts the completed hash computation into digest and returns 1
 *
 *  Exceptions: Returns 0 if:
 *                s == NULL,
 *                s->iv == NULL,
 *                digest == NULL.
 *
 *  Note:       The state buffer 'leftover' is left in memory after processing.
 *              If your application intends to have sensitive data in this
 *              buffer, remind to erase it after the data has been processed.
 */
int32_t sha256_final (uint8_t *digest, Sha256State_t s);


#endif
