
#ifndef __HMAC_H__
#define __HMAC_H__

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
 *  hmac.h -- Interface to an HMAC implementation.
 *
 *  Overview:   HMAC is a message authentication code based on hash functions.
 *              TinyCrypt hard codes SHA-256 as the hash function. A message
 *              authentication code based on hash functions is also called a
 *              keyed cryptographic hash function since it performs a
 *              transformation specified by a key in an arbitrary length data
 *              set into a fixed length data set (also called tag).
 *
 *  Security:   The security of the HMAC depends on the length of the key and
 *              on the security of the hash function. Note that HMAC primitives
 *              are much less affected by collision attacks than their
 *              corresponding hash functions.
 *
 *  Requires:   SHA-256
 *
 *  Usage:      1) call hmac_set_key to set the HMAC key.
 *
 *              2) call hmac_init to initialize a struct hash_state before
 *              processing the data.
 *
 *              3) call hmac_update to process the next input segment;
 *              hmac_update can be called as many times as needed to process
 *              all of the segments of the input; the order is important.
 *
 *              4) call hmac_final to out put the tag.
 */

#include "sha256.h"

struct hmac_state_struct {
  struct sha256_state_struct hash_state; /* the internal state required by h */
  uint8_t key[2*SHA256_BLOCK_SIZE];      /* HMAC key schedule */
};
typedef struct hmac_state_struct *HmacState_t;

/*
 *  HMAC set key procedure.
 *
 *  Effects:  Configures ctx to use key and returns 1
 *
 *  Exceptions:  Returns 0 if
 *                ctx == NULL or
 *                key == NULL or
 *                key_size == 0.
 */
int32_t hmac_set_key (
  HmacState_t ctx,      /* IN/OUT -- the struct hmac_state_struct to initial */
  const uint8_t *key,   /* IN -- the HMAC key to configure */
  uint32_t key_size);

/*
 *  HMAC init procedure.
 *
 *  Effects:  Initializes ctx to begin the next HMAC operation and returns 1
 *
 *  Exceptions: Returns 0 if:
 *                ctx == NULL or
 *                key == NULL.
 */
int32_t hmac_init (
  HmacState_t ctx);   /* IN/OUT -- struct hmac_state_struct buffer to init */

/*
 *  HMAC update procedure.
 *
 *  Assumes:    state has been initialized by hmac_init
 *
 *  Effects:    Mixes data_length bytes addressed by data into state and
 *              returns 1
 *
 *  Exceptions: Returns 0 if:
 *                ctx == NULL or
 *                key == NULL.
 *
 */
int32_t hmac_update (
  HmacState_t ctx,        /* IN/OUT -- state of HMAC computation so far */
  const void *data,       /* IN -- data to incorporate into state */
  uint32_t data_length);  /* IN -- size of data in bytes */

/*
 *  HMAC final procedure.
 *
 *  Assumes:    The tag bufer is at least sizeof(hmac_tag_size(state)) bytes
 *              state has been initialized by hmac_init
 *
 *  Effects:    Writes the HMAC tag into the tag buffer and returns 1
 *
 *  Exceptions: Returns 0 if:
 *                tag == NULL or
 *                ctx == NULL or
 *                key == NULL or
 *                taglen != SHA256_DIGEST_SIZE.
 *
 */
int32_t hmac_final (
  uint8_t *tag,       /* IN/OUT -- buffer to receive computed HMAC tag */
  uint32_t taglen,    /* IN -- size of tag in bytes */
  HmacState_t ctx);   /* IN -- the HMAC state for computing tag */

#endif
