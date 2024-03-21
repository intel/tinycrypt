/* hkdf.c - TinyCrypt implementation of HKDF-SHA256 */

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

#include <tinycrypt/hkdf.h>
#include <tinycrypt/sha256.h>
#include <tinycrypt/constants.h>
#include <tinycrypt/utils.h>

int tc_hkdf_extract(const void *ikm, size_t ikmlen, const void *salt,
		    size_t saltlen, void *prk)
{
	uint8_t _salt[TC_SHA256_DIGEST_SIZE];
	struct tc_hmac_state_struct hmac_state;
	unsigned int rc;

	if (ikm == (const void *) 0 ||
	    ikmlen == 0 ||
	    prk == (void *) 0) {
		return TC_CRYPTO_FAIL;
	}

	if (salt == (const void *) 0) {
		_set(_salt, 0, TC_SHA256_DIGEST_SIZE);
		rc = tc_hmac_set_key(&hmac_state, _salt, TC_SHA256_DIGEST_SIZE);
	} else {
		rc = tc_hmac_set_key(&hmac_state, salt, saltlen);
	}

	if (rc != TC_CRYPTO_SUCCESS) {
		return TC_CRYPTO_FAIL;
	}

	rc = tc_hmac_init(&hmac_state);
	if (rc != TC_CRYPTO_SUCCESS) {
		return TC_CRYPTO_FAIL;
	}

	rc = tc_hmac_update(&hmac_state, ikm, ikmlen);
	if (rc != TC_CRYPTO_SUCCESS) {
		return TC_CRYPTO_FAIL;
	}

	return tc_hmac_final(prk, TC_SHA256_DIGEST_SIZE, &hmac_state);
}

int tc_hkdf_expand(const void *prk, const void *info, size_t infolen,
		   size_t L, void *okm)
{
	uint8_t T[TC_SHA256_DIGEST_SIZE];
	struct tc_hmac_state_struct hmac_state;
	uint16_t off;
	uint16_t len;
	uint8_t counter;
	uint8_t *u8okm;
	bool first;
	int rc;

	if (prk == (const void *) 0 || okm == (void *) 0) {
		return TC_CRYPTO_FAIL;
	}

	u8okm = (uint8_t *)okm;
	len = L;
	counter = 1;
	first = true;
	for (off = 0; len > 0; off += TC_SHA256_DIGEST_SIZE, ++counter) {
		rc = tc_hmac_set_key(&hmac_state, prk, TC_SHA256_DIGEST_SIZE);
		if (rc != TC_CRYPTO_SUCCESS) {
			return TC_CRYPTO_FAIL;
		}

		rc = tc_hmac_init(&hmac_state);
		if (rc != TC_CRYPTO_SUCCESS) {
			return TC_CRYPTO_FAIL;
		}

		if (!first) {
			rc = tc_hmac_update(&hmac_state, T,
					    TC_SHA256_DIGEST_SIZE);
			if (rc != TC_CRYPTO_SUCCESS) {
				return TC_CRYPTO_FAIL;
			}
		} else {
			first = false;
		}

		rc = tc_hmac_update(&hmac_state, info, infolen);
		if (rc != TC_CRYPTO_SUCCESS) {
			return TC_CRYPTO_FAIL;
		}

		rc = tc_hmac_update(&hmac_state, &counter, 1);
		if (rc != TC_CRYPTO_SUCCESS) {
			return TC_CRYPTO_FAIL;
		}

		rc = tc_hmac_final(T, TC_SHA256_DIGEST_SIZE, &hmac_state);
		if (rc != TC_CRYPTO_SUCCESS) {
			return TC_CRYPTO_FAIL;
		}

		if (len > TC_SHA256_DIGEST_SIZE) {
			memcpy(&u8okm[off], T, TC_SHA256_DIGEST_SIZE);
			len -= TC_SHA256_DIGEST_SIZE;
		} else {
			memcpy(&u8okm[off], T, len);
			len = 0;
		}
	}

	return TC_CRYPTO_SUCCESS;
}
