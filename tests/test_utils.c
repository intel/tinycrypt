/* test_utils.c - TinyCrypt c ommon functions for tests */
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
 *  test_utils.c -- Common functions for tests.
 */
#include "test_utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void show_str (const char *label, const uint8_t *s, size_t len) {
  uint32_t i;
  fprintf (stderr, "%s = ", label);
  for (i = 0; i < (uint32_t) len; ++i) {
    fprintf (stderr, "%02x", s[i]);
  }
  fprintf (stderr, "\n");
}

void fatal (
    uint32_t testnum, const void *expected, size_t expectedlen,
    const void *computed, size_t computedlen) {

  fprintf (stderr, "\tTest #%d Failed!\n", testnum);
  show_str ("\t\tExpected", expected, expectedlen);
  show_str ("\t\tComputed  ", computed, computedlen);
  fprintf(stderr, "\n");
}

void check_result (
    uint32_t testnum, const void *expected, size_t expectedlen,
    const void *computed, size_t computedlen, uint32_t verbose) {

  if (expectedlen != computedlen) {
    fprintf(stderr, "The length of the computed buffer (%zu)", computedlen);
    fprintf(stderr, "does not match the expected length (%zu).", expectedlen);
    exit (-1);
  } else if (memcmp (computed, expected, computedlen) != 0) {
      fatal (testnum, expected, expectedlen, computed, computedlen);
      exit (-1);
  }
  if (verbose) {
    printf("Success!\n");
  }
}
