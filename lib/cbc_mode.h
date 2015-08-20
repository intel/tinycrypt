
#ifndef __CBC_MODE_H__
#define __CBC_MODE_H__

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
 *  cbc_mode.h -- Interface to a CBC mode implementation.
 *
 *  Overview: CBC (for "cipher block chaining") mode is a NIST approved mode of
 *            operation defined in SP 800-38a. It can be used with any block
 *            cipher to provide confidentiality of strings whose lengths are
 *            multiples of the block_size of the underlying block cipher.
 *            TinyCrypt hard codes AES as the block cipher.
 *
 *  Security: CBC mode provides data confidentiality given that the maximum
 *            number q of blocks encrypted under a single key satisfies
 *            q < 2^63, which is not a practical constraint (it is considered a
 *            good practice to replace the encryption when q == 2^56). CBC mode
 *            provides NO data integrity.
 *
 *            CBC mode assumes that the IV value input into the cbc_mode_encrypt
 *            is randomly generated. The TinyCrypt library provides HMAC-PRNG
 *            module, which generates suitable IVs. Other methods for generating
 *            IVs are acceptable, provided that the values of the IVs generated
 *            appear random to any adversary, including someone with complete
 *            knowledge of the system design.
 *
 *            The randomness property on which CBC mode's security depends is
 *            the unpredictability of the IV. Since it is unpredictable, this
 *            means in practice that CBC mode requires that the IV is stored
 *            somehow with the ciphertext in order to recover the plaintext.
 *
 *            TinyCrypt CBC encryption prepends the IV to the ciphertext,
 *            because this affords a more efficient (few buffers) decryption.
 *            Hence cbc_mode_encrypt assumes the ciphertext buffer is always
 *            16 bytes larger than the plaintext buffer.
 *
 *  Requires: AES-128
 *
 *  Usage:    1) call cbc_mode_encrypt to encrypt data.
 *
 *            2) call cbc_mode_decrypt to decrypt data.
 *
 */

#include "aes.h"

/*
 *  CBC encryption procedure.
 *
 *  Assumes:    - sched has been configured by aes_set_encrypt_key;
 *              - iv contains a 16 byte random string;
 *              - out buffer is large enough to hold the ciphertext + iv;
 *              - out buffer is a contiguous buffer;
 *              - in holds the plaintext and is a contiguous buffer;
 *              - inlen gives the number of bytes in the in buffer.
 *
 *  Effects:    CBC encrypts inlen bytes of the in buffer into the out buffer
 *              using the encryption key schedule provided, prepends iv
 *              to out, and returns 1.
 *
 *  Exceptions: Returns 0 if:
 *                out == NULL or
 *                in == NULL or
 *                ctr == NULL or
 *                sched == NULL or
 *                inlen == 0 or
 *                (inlen % AES_BLOCK_SIZE) != 0 or
 *                (outlen % AES_BLOCK_SIZE) != 0 or
 *                outlen != inlen + AES_BLOCK_SIZE.
 */
int32_t cbc_mode_encrypt (
  uint8_t *out,                 /* IN/OUT -- buffer to receive the ciphertext */
  uint32_t outlen,              /* IN -- length of ciphertext buffer in bytes */
  const uint8_t *in,            /* IN -- plaintext to encrypt */
  uint32_t inlen,               /* IN -- length of plaintext buffer in bytes */
  const uint8_t *iv,            /* IN -- the IV for the this encrypt/decrypt */
  const AesKeySched_t sched);   /* IN --  AES key schedule for this encrypt */

/*
 *  CBC decryption procedure.
 *
 *  Assumes:    - in == iv + ciphertext, i.e. the iv and the ciphertext are
 *                contiguous. This allows for a very efficient decryption
 *                algorithm that would not otherwise be possible;
 *              - sched was configured by aes_set_decrypt_key;
 *              - out buffer is large enough to hold the decrypted plaintext
 *              and is a contiguous buffer;
 *              - inlen gives the number of bytes in the in buffer.
 *
 *  Effects:    CBC decrypts inlen bytes of the in buffer into the out buffer
 *              using the encryption key schedule provided by a, and returns 1.
 *
 *  Exceptions: Returns 0 if:
 *                out == NULL or
 *                in == NULL or
 *                sched == NULL or
 *                inlen == 0 or
 *                outlen == 0 or
 *                (inlen % AES_BLOCK_SIZE) != 0 or
 *                (outlen % AES_BLOCK_SIZE) != 0 or
 *                outlen != inlen + AES_BLOCK_SIZE.
 *
 */
int32_t cbc_mode_decrypt (
  uint8_t *out,               /* IN/OUT -- buffer to receive decrypted data */
  uint32_t outlen,            /* IN -- length of plaintext buffer in bytes */
  const uint8_t *in,          /* IN -- ciphertext to decrypt, including IV */
  uint32_t inlen,             /* IN -- length of ciphertext buffer in bytes */
  const uint8_t *iv,          /* IN -- the IV for the this encrypt/decrypt */
  const AesKeySched_t sched); /* IN --  AES key schedule for this decrypt */

#endif
