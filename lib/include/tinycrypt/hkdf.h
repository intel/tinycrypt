/* hkdf.h - TinyCrypt interface to an HKDF implementation */

/*
 *  Copyright (C) 2020 by JUUL Labs, All Rights Reserved.
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
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief Interface to an HKDF SHA-256 implementation.
 *
 *  Overview:   HKDF is a simple (HMAC)-based key derivation function (HKDF),
 *              which can be used as a building block in various protocols and
 *              applications. TinyCrypt uses HMAC with hard coded SHA-256 as
 *              the hash function. HKDF is stateless, so no initialization
 *              or context pointers are required for its use.
 *
 *  Requires:   HMAC
 *
 *  Usage:      1) call tc_hkdf_extract to create a new pseudorandom key. When
 *                 a PRK with good random properties is already available by
 *                 the HKDF client, calling this function might be skipped.
 *
 *              2) call tc_hkdf_expand to expand the given pseudorandom key
 *                 into a given number of octets. Usually the PRK will come
 *                 from the output of tc_hkdf_extract.
 */

#ifndef __TC_HKDF_H__
#define __TC_HKDF_H__

#include <tinycrypt/sha256.h>
#include <tinycrypt/hmac.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief HKDF extract
 *  Outputs a pseudorandom key of size TC_SHA256_DIGEST_SIZE from input
 *  keying material
 *  @return returns TC_CRYPTO_SUCCCESS (1)
 *          returns TC_CRYPTO_FAIL (0) if:
 *                ikm == NULL or
 *                ikmlen == 0 or
 *                prk == NULL
 *  @param ikm IN -- input keying material
 *  @param ikmlen IN - size of keying material
 *  @param salt IN - optional salt value
 *  @param saltlen IN - size of salt (not used if salt == NULL)
 *  @param prk OUT - output pseudorandom key for expand
 */
int tc_hkdf_extract(const void *ikm, size_t ikmlen, const void *salt,
		    size_t saltlen, void *prk);

/**
 *  @brief HKDF expand
 *  Expands a key into L number of bytes written on okm
 *  @return returns TC_CRYPTO_SUCCESS (1)
 *          returns TC_CRYPTO_FAIL (0) if:
 *                prk == NULL or
 *                okm == NULL
 *  @param prk IN -- a pseudorandom key (can be generated with tc_hkdf_extract)
 *  @param info IN -- an application specific information tag
 *  @param infolen IN -- size of info in bytes
 *  @param L IN -- number of bytes of the key to derive into okm
 *  @param okm OUT -- buffer for the key derivation output
 */
int tc_hkdf_expand(const void *prk, const void *info, size_t infolen,
		   size_t L, void *okm);

#ifdef __cplusplus
}
#endif

#endif /*__TC_HKDF_H__*/
