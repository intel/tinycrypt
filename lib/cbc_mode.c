
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
 *  cbc_mode.c -- an implementation of CBC mode encryption and decryption.
 *
 *  See the corresponding header file for more information.
 *
 */

#include "cbc_mode.h"
#include "utils.h"

int32_t cbc_mode_encrypt (
    uint8_t *out,
    uint32_t outlen,
    const uint8_t *in,
    uint32_t inlen,
    const uint8_t *iv,
    const AesKeySched_t sched) {

  uint8_t buffer[AES_BLOCK_SIZE];
  uint32_t n, m;

  /* input sanity check: */
  if (out == (uint8_t *) 0 ||
      in == (const uint8_t *) 0 ||
      sched == (AesKeySched_t) 0 ||
      inlen == 0 ||
      outlen == 0 ||
      (inlen % AES_BLOCK_SIZE) != 0 ||
      (outlen % AES_BLOCK_SIZE) != 0 ||
      outlen != inlen + AES_BLOCK_SIZE) {
    return 0;
  }

  /* copy iv to the buffer */
  (void) copy (buffer, AES_BLOCK_SIZE, iv, AES_BLOCK_SIZE);
  /* copy iv to the output buffer */
  (void) copy (out, AES_BLOCK_SIZE, iv, AES_BLOCK_SIZE);
  out += AES_BLOCK_SIZE;

  for (n = m = 0; n < inlen; ++n) {
    buffer[m++] ^= *in++;
    if (m == AES_BLOCK_SIZE) {
      (void) aes_encrypt (buffer, buffer, sched);
      (void) copy (out, AES_BLOCK_SIZE, buffer, AES_BLOCK_SIZE);
      out += AES_BLOCK_SIZE;
      m = 0;
    }
  }

  return 1;
}

int32_t cbc_mode_decrypt (
    uint8_t *out,
    uint32_t outlen,
    const uint8_t *in,
    uint32_t inlen,
    const uint8_t *iv,
    const AesKeySched_t sched) {

  uint8_t buffer[AES_BLOCK_SIZE];
  const uint8_t *p;
  uint32_t n, m;

  /* sanity check the inputs */
  if (out == (uint8_t *) 0 ||
      in == (const uint8_t *) 0 ||
      sched == (AesKeySched_t) 0 ||
      inlen == 0 ||
      outlen == 0 ||
      (inlen % AES_BLOCK_SIZE) != 0 ||
      (outlen % AES_BLOCK_SIZE) != 0 ||
      outlen != inlen - AES_BLOCK_SIZE) {
    return 0;
  }

  /* Note that in == iv + ciphertext, i.e. the iv and the ciphertext are
   * contiguous. This allows for a very efficient decryption algorithm that
   * would not otherwise be possible. */
  p = iv;
  for (n = m = 0; n < inlen; ++n) {
    if ((n % AES_BLOCK_SIZE) == 0) {
      (void) aes_decrypt (buffer, in, sched);
      in += AES_BLOCK_SIZE;
      m = 0;
    }
    *out++ = buffer[m++] ^ *p++;
  }

  return 1;
}
