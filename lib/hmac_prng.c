/* hmac_prng.c - TinyCrypt implementation of HMAC-PRNG */
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
 *  hmac_prng.c -- An implementation of HMAC-PRNG.
 *
 *  See the corresponding header file for more information.
 *
 */

#include "hmac_prng.h"
#include "hmac.h"
#include "utils.h"

/* min bytes in the seed string.
 * MIN_SLEN*8 must be at least the expected security level. */
static const uint32_t MIN_SLEN = 32;

/* max bytes in the seed string;
 * SP800-90A specifies a maximum of 2^35 bits (i.e., 2^32 bytes).*/
static const uint32_t MAX_SLEN = UINT32_MAX;

/* max bytes in the personalization string;
 * SP800-90A specifies a maximum of 2^35 bits (i.e., 2^32 bytes).*/
static const uint32_t MAX_PLEN = UINT32_MAX;

/* max bytes in the additional_info string;
 * SP800-90A specifies a maximum of 2^35 bits (i.e., 2^32 bytes).*/
static const uint32_t MAX_ALEN = UINT32_MAX;

/* max number of generates between re-seeds;
 * TinyCrypt accepts up to (2^32 - 1) which is the maximal value of
 * a uint32_t variable, while SP800-90A specifies a maximum of 2^48.*/
static const uint32_t MAX_GENS = UINT32_MAX;

/* maximum bytes per generate call;
 * SP800-90A specifies a maximum up to 2^19.*/
static const uint32_t MAX_OUT = (1 << 19);

/*
 * Assumes: prng != NULL, e != NULL, len >= 0.
 */
static void update (HmacPrng_t prng, const uint8_t *e, uint32_t len) {
  const uint8_t separator0 = 0x00;
  const uint8_t separator1 = 0x01;

  /* use current state, e and separator 0 to compute a new prng key: */
  (void) hmac_init (&prng->h);
  (void) hmac_update (&prng->h, prng->v, sizeof (prng->v));
  (void) hmac_update (&prng->h, &separator0, sizeof (separator0));
  (void) hmac_update (&prng->h, e, len);
  (void) hmac_final (prng->key, sizeof(prng->key), &prng->h);
  /* configure the new prng key into the prng's instance of hmac */
  (void) hmac_set_key (&prng->h, prng->key, sizeof (prng->key));

  /* use the new key to compute a new state variable v */
  (void) hmac_init (&prng->h);
  (void) hmac_update (&prng->h, prng->v, sizeof (prng->v));
  (void) hmac_final (prng->v, sizeof(prng->v), &prng->h);

  /* use current state, e and separator 1 to compute a new prng key: */
  (void) hmac_init (&prng->h);
  (void) hmac_update (&prng->h, prng->v, sizeof (prng->v));
  (void) hmac_update (&prng->h, &separator1, sizeof (separator1));
  (void) hmac_update (&prng->h, e, len);
  (void) hmac_final (prng->key, sizeof(prng->key), &prng->h);
  /* configure the new prng key into the prng's instance of hmac */
  (void) hmac_set_key (&prng->h, prng->key, sizeof (prng->key));

  /* use the new key to compute a new state variable v */
  (void) hmac_init (&prng->h);
  (void) hmac_update (&prng->h, prng->v, sizeof (prng->v));
  (void) hmac_final (prng->v, sizeof(prng->v), &prng->h);
}

int32_t hmac_prng_init (
  HmacPrng_t prng,                /* IN/OUT -- the PRNG state to initialize */
  const uint8_t *personalization, /* IN -- personalization string */
  uint32_t plen) {                /* IN -- personalization length in bytes */

  /* input sanity check: */
  if (prng == (HmacPrng_t) 0 ||
      personalization == (uint8_t*) 0 ||
      plen > MAX_PLEN) {
    return 0;
  }

  /* put the generator into a known state: */
  set (prng->key, 0x00, sizeof (prng->key));
  set (prng->v, 0x01, sizeof (prng->v));
  hmac_set_key (&prng->h, prng->key, sizeof (prng->key));
  /* update assumes SOME key has been configured into HMAC */

  update (prng, personalization, plen);

  /* force a reseed before allowing hmac_prng_generate to succeed: */
  prng->countdown = 0;

  return 1;
}

int32_t hmac_prng_reseed (
  HmacPrng_t prng,
  const uint8_t *seed,
  uint32_t seedlen,
  const uint8_t *additional_input,
  uint32_t additionallen) {

  /* input sanity check: */
  if (prng == (HmacPrng_t) 0 ||
      seed == (const uint8_t *) 0 ||
      seedlen < MIN_SLEN ||
      seedlen > MAX_SLEN) {
    return 0;
  } else if (additional_input != (const uint8_t *) 0) {
    /* Abort if additional_input is provided but has inappropriate length */
    if (additionallen == 0 ||
        additionallen > MAX_ALEN) {
      return 0;
    } else {
      /* call update for the seed and additional_input */
      update (prng, seed, seedlen);
      update (prng, additional_input, additionallen);
    }
  } else {
    /* call update only for the seed */
    update (prng, seed, seedlen);
  }

  /* ... and enable hmac_prng_get */
  prng->countdown = MAX_GENS;

  return 1;
}

int32_t hmac_prng_generate (
  uint8_t *out,         /* IN/OUT -- buffer to receive output */
  uint32_t outlen,      /* IN -- size of out buffer in bytes */
  HmacPrng_t prng) {    /* IN/OUT -- the PRNG state */
  uint32_t bufferlen;

  /* input sanity check: */
  if (out == (uint8_t *) 0 ||
      prng == (HmacPrng_t) 0 ||
      outlen == 0 ||
      outlen > MAX_OUT) {
    return 0;
  } else if (prng->countdown == 0) {
    return -1;
  }

  prng->countdown--;

  while (outlen != 0) {
    /* operate HMAC in OFB mode to create "random" outputs */
    (void) hmac_init (&prng->h);
    (void) hmac_update (&prng->h, prng->v, sizeof (prng->v));
    (void) hmac_final (prng->v, sizeof(prng->v), &prng->h);

    bufferlen = (SHA256_DIGEST_SIZE > outlen) ? outlen : SHA256_DIGEST_SIZE;
    (void) copy (out, bufferlen, prng->v, bufferlen);

    out += bufferlen;
    outlen = (outlen > SHA256_DIGEST_SIZE) ? (outlen - SHA256_DIGEST_SIZE) : 0;
  }

  /* block future PRNG compromises from revealing past state */
  update (prng, prng->v, SHA256_DIGEST_SIZE);

  return 1;
}
