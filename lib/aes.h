/* aes.h - TinyCrypt interface to an AES-128 implementation. */
#ifndef __AES_H__
#define __AES_H__

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
 *  aes.h -- Interface to an AES-128 implementation.
 *
 *  Overview:   AES-128 is a NIST approved block cipher specified in
 *              FIPS 197. Block ciphers are deterministic algorithms that
 *              perform a transformation specified by a symmetric key in fixed-
 *              length data sets, also called blocks.
 *
 *  Security:   AES-128 provides approximately 128 bits of security.
 *
 *  Usage:      1) call aes128_set_encrypt/decrypt_key to set the key.
 *
 *              2) call aes_encrypt/decrypt to process the data.
 */

#include<stdint.h>

#define Nb (4)  // number of columns (32-bit words) comprising the state
#define Nk (4)  // number of 32-bit words comprising the key
#define Nr (10) // number of rounds
#define AES_BLOCK_SIZE (Nb*Nk)
#define AES_KEY_SIZE (Nb*Nk)

struct aes_key_sched_struct {
  uint32_t words[Nb*(Nr+1)];
};
typedef struct aes_key_sched_struct *AesKeySched_t;

/*
 *  Set AES-128 encryption key.
 *
 *  Effects:    Uses key k to initialize s and returns 1.
 *
 *  Exceptions: Returns 0 if:
 *                s == NULL or
 *                k == NULL.
 *
 *  Note:       This implementation skips the additional steps required for keys
 *              larger than 128 bits, and must not be used for AES-192 or
 *              AES-256 key schedule -- see FIPS 197 for details.
 *
 */
int32_t aes128_set_encrypt_key (
  AesKeySched_t s,          /* IN/OUT -- inited struct aes_key_sched_struct */
  const uint8_t *k);        /* IN -- points to the AES key */

/*
 *  AES-128 Encryption procedure.
 *
 *  Assumes:    s was initialized by aes_set_encrypt_key;
 *              out and in point to 16 byte buffers.
 *
 *  Effects:    Encrypts contents of in buffer into out buffer under key;
 *              schedule s and returns 1.
 *
 *  Exceptions: Returns 0 if:
 *                out == NULL or
 *                in == NULL or
 *                s == NULL.
 */
int32_t aes_encrypt (
  uint8_t *out,       			/* IN/OUT -- buffer to receive ciphertext block */
  const uint8_t *in,  			/* IN -- a plaintext block to encrypt */
  const AesKeySched_t s);   /* IN -- initialized AES key schedule */

/*
 *  Set the AES-128 decryption key.
 *
 *  Effects:    Uses key k to initialize s and returns 1.
 *
 *  Exceptions: Returns 0 if:
 *                s == NULL or
 *                k == NULL.
 *
 *  note:       This is the implementation of the straightforward inverse cipher
 *              using the cipher documented in FIPS-197 figure 12, not the
 *              equivalent inverse cipher presented in Figure 15.
 *
 *              This routine skips the additional steps required for keys larger
 *              than 128, and must not be used for AES-192 or AES-256 key
 *              schedule -- see FIPS 197 for details.
 */
int32_t aes128_set_decrypt_key (
  AesKeySched_t s,         	/* IN/OUT -- inited struct aes_key_sched_struct */
  const uint8_t *k); 				/* IN -- points to the AES key */

/*
 *  AES-128 Encryption procedure.
 *
 *  Assumes:    s was initialized by aes_set_encrypt_key
 *              out and in point to 16 byte buffers.
 *           
 *  Effects:    Decrypts in buffer into out buffer under key schedule s and
 *              returns 1.
 *           
 *  Exceptions: Returns 0 if:
 *                out is NULL or
 *                in is NULL or
 *                s is NULL.
 */
int32_t aes_decrypt (
  uint8_t *out,       			/* IN/OUT -- buffer to receive ciphertext block */
  const uint8_t *in,  			/* IN -- a plaintext block to encrypt */
  const AesKeySched_t s);   /* IN -- initialized AES key schedule */

#endif
