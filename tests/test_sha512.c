/*  test_sha512.c - TinyCrypt implementation of some SHA-512 tests */

/*
 *  Copyright (C) 2020 by Intel Corporation, All Rights Reserved.
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

/*
  DESCRIPTION
  This module tests the following SHA512 routines:

  Scenarios tested include:
  - NIST SHA512 test vectors
*/

#include <tinycrypt/sha512.h>
#include <tinycrypt/constants.h>
#include <test_utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * NIST SHA512 test vector 1.
 */
unsigned int test_1(void)
{
        unsigned int result = TC_PASS;

        TC_PRINT("SHA512 test #1:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0xdd, 0xaf, 0x35, 0xa1, 0x93, 0x61, 0x7a, 0xba,
            0xcc, 0x41, 0x73, 0x49, 0xae, 0x20, 0x41, 0x31,
            0x12, 0xe6, 0xfa, 0x4e, 0x89, 0xa9, 0x7e, 0xa2,
            0x0a, 0x9e, 0xee, 0xe6, 0x4b, 0x55, 0xd3, 0x9a,
            0x21, 0x92, 0x99, 0x2a, 0x27, 0x4f, 0xc1, 0xa8,
            0x36, 0xba, 0x3c, 0x23, 0xa3, 0xfe, 0xeb, 0xbd,
            0x45, 0x4d, 0x44, 0x23, 0x64, 0x3c, 0xe8, 0x0e,
            0x2a, 0x9a, 0xc9, 0x4f, 0xa5, 0x4c, 0xa4, 0x9f,
        };
        const char *m = "abc";
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, (const uint8_t *) m, strlen(m));
        (void)tc_sha512_final(digest, &s);
        result = check_result(1, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

/*
 * NIST SHA512 test vector 2.
 */
unsigned int test_2(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #2:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x20, 0x4a, 0x8f, 0xc6, 0xdd, 0xa8, 0x2f, 0x0a,
            0x0c, 0xed, 0x7b, 0xeb, 0x8e, 0x08, 0xa4, 0x16,
            0x57, 0xc1, 0x6e, 0xf4, 0x68, 0xb2, 0x28, 0xa8,
            0x27, 0x9b, 0xe3, 0x31, 0xa7, 0x03, 0xc3, 0x35,
            0x96, 0xfd, 0x15, 0xc1, 0x3b, 0x1b, 0x07, 0xf9,
            0xaa, 0x1d, 0x3b, 0xea, 0x57, 0x78, 0x9c, 0xa0,
            0x31, 0xad, 0x85, 0xc7, 0xa7, 0x1d, 0xd7, 0x03,
            0x54, 0xec, 0x63, 0x12, 0x38, 0xca, 0x34, 0x45,
        };
        const char *m = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, (const uint8_t *) m, strlen(m));
        (void) tc_sha512_final(digest, &s);

        result = check_result(2, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_3(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #3:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x29, 0x6e, 0x22, 0x67, 0xd7, 0x4c, 0x27, 0x8d,
            0xaa, 0xaa, 0x94, 0x0d, 0x17, 0xb0, 0xcf, 0xb7,
            0x4a, 0x50, 0x83, 0xf8, 0xe0, 0x69, 0x72, 0x6d,
            0x8c, 0x84, 0x1c, 0xbe, 0x59, 0x6e, 0x04, 0x31,
            0xcb, 0x77, 0x41, 0xa5, 0xb5, 0x0f, 0x71, 0x66,
            0x6c, 0xfd, 0x54, 0xba, 0xcb, 0x7b, 0x00, 0xae,
            0xa8, 0x91, 0x49, 0x9c, 0xf4, 0xef, 0x6a, 0x03,
            0xc8, 0xa8, 0x3f, 0xe3, 0x7c, 0x3f, 0x7b, 0xaf,
        };
        const uint8_t m[1] = { 0xbd };
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(3, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_4(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #4:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x09, 0xa9, 0x85, 0xc1, 0x5f, 0xa5, 0xcc, 0x68,
            0xa8, 0x96, 0x8f, 0xfa, 0xea, 0xf3, 0xb5, 0xec,
            0x23, 0x45, 0x69, 0xad, 0x56, 0x74, 0x50, 0x39,
            0x4c, 0x07, 0x5b, 0x90, 0x61, 0xc8, 0xf7, 0xdf,
            0x58, 0xff, 0x11, 0x29, 0x95, 0x70, 0x18, 0x82,
            0x16, 0xc6, 0x31, 0xde, 0x60, 0x4d, 0xf0, 0xab,
            0x08, 0xcd, 0xd1, 0x93, 0x29, 0x1c, 0xe5, 0x76,
            0x3a, 0xcd, 0xc4, 0x27, 0xdf, 0x06, 0x04, 0x89,
        };
        const uint8_t m[4] = { 0xc9, 0x8c, 0x8e, 0x55 };
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(4, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_5(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #5:\n");

        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x2c, 0x24, 0x81, 0x27, 0x8f, 0x62, 0xcd, 0x07,
            0x72, 0x63, 0x83, 0xb0, 0x36, 0x77, 0x53, 0x06,
            0xae, 0x6b, 0x69, 0x3f, 0x19, 0x9a, 0x6c, 0x70,
            0x0f, 0x73, 0x5f, 0xe2, 0x25, 0x07, 0xc9, 0x08,
            0x4b, 0xb9, 0x1c, 0xe5, 0xf6, 0x45, 0x8d, 0x3c,
            0x39, 0x26, 0x51, 0x49, 0x70, 0x22, 0x6c, 0x56,
            0x34, 0x64, 0x72, 0x3a, 0xa9, 0x9c, 0x21, 0x0b,
            0x77, 0x51, 0x88, 0x30, 0x57, 0x6f, 0x8c, 0x0b,
        };
        uint8_t m[55];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x00, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(5, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_6(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #6:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x21, 0x46, 0xaa, 0x8a, 0xb6, 0x0c, 0x48, 0xac,
            0xff, 0x43, 0xae, 0x8c, 0x33, 0xc5, 0xda, 0x4c,
            0x25, 0x86, 0xf2, 0x0a, 0x39, 0xf8, 0xf1, 0x30,
            0x8a, 0xef, 0xb6, 0xf8, 0x33, 0xb7, 0x58, 0xad,
            0x71, 0x58, 0xbd, 0x5e, 0x9a, 0x38, 0x6e, 0x45,
            0xfe, 0xba, 0x44, 0x6f, 0x33, 0x85, 0x5d, 0x39,
            0x38, 0x57, 0xb5, 0x57, 0xfe, 0x8b, 0xa6, 0xfe,
            0x52, 0x36, 0x4e, 0x7a, 0x7a, 0xf3, 0xbe, 0x9b,
        };
        uint8_t m[56];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x00, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(6, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_7(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #7:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x90, 0x4f, 0x18, 0x92, 0xec, 0x5c, 0x43, 0xc5,
            0x57, 0x19, 0x93, 0x25, 0xfd, 0xa7, 0x9c, 0xac,
            0xae, 0xe2, 0xe8, 0xf1, 0xb4, 0xa1, 0xd4, 0x1b,
            0x85, 0xc8, 0x93, 0xd9, 0x67, 0xc3, 0x20, 0x9f,
            0x0c, 0x58, 0x08, 0x1c, 0x0c, 0x9a, 0x60, 0x83,
            0xf8, 0x5f, 0xd4, 0x86, 0x66, 0x11, 0xdf, 0xeb,
            0x49, 0x0c, 0x11, 0xf3, 0x16, 0x3c, 0x12, 0xf4,
            0xf0, 0x57, 0x9a, 0xdd, 0xa2, 0xc6, 0x81, 0x00,
        };
        uint8_t m[57];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x00, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(7, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_8(void)
{
        unsigned int result = TC_PASS;

        TC_PRINT("SHA512 test #8:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x7b, 0xe9, 0xfd, 0xa4, 0x8f, 0x41, 0x79, 0xe6,
            0x11, 0xc6, 0x98, 0xa7, 0x3c, 0xff, 0x09, 0xfa,
            0xf7, 0x28, 0x69, 0x43, 0x1e, 0xfe, 0xe6, 0xea,
            0xad, 0x14, 0xde, 0x0c, 0xb4, 0x4b, 0xbf, 0x66,
            0x50, 0x3f, 0x75, 0x2b, 0x7a, 0x8e, 0xb1, 0x70,
            0x83, 0x35, 0x5f, 0x3c, 0xe6, 0xeb, 0x7d, 0x28,
            0x06, 0xf2, 0x36, 0xb2, 0x5a, 0xf9, 0x6a, 0x24,
            0xe2, 0x2b, 0x88, 0x74, 0x05, 0xc2, 0x00, 0x81,
        };
        uint8_t m[64];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x00, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(8, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_9(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #9:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0xca, 0x3d, 0xff, 0x61, 0xbb, 0x23, 0x47, 0x7a,
            0xa6, 0x08, 0x7b, 0x27, 0x50, 0x82, 0x64, 0xa6,
            0xf9, 0x12, 0x6e, 0xe3, 0xa0, 0x04, 0xf5, 0x3c,
            0xb8, 0xdb, 0x94, 0x2e, 0xd3, 0x45, 0xf2, 0xf2,
            0xd2, 0x29, 0xb4, 0xb5, 0x9c, 0x85, 0x92, 0x20,
            0xa1, 0xcf, 0x19, 0x13, 0xf3, 0x42, 0x48, 0xe3,
            0x80, 0x3b, 0xab, 0x65, 0x0e, 0x84, 0x9a, 0x3d,
            0x9a, 0x70, 0x9e, 0xdc, 0x09, 0xae, 0x4a, 0x76,
        };
        uint8_t m[1000];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x00, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(9, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_10(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #10:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x32, 0x9c, 0x52, 0xac, 0x62, 0xd1, 0xfe, 0x73,
            0x11, 0x51, 0xf2, 0xb8, 0x95, 0xa0, 0x04, 0x75,
            0x44, 0x5e, 0xf7, 0x4f, 0x50, 0xb9, 0x79, 0xc6,
            0xf7, 0xbb, 0x7c, 0xae, 0x34, 0x93, 0x28, 0xc1,
            0xd4, 0xcb, 0x4f, 0x72, 0x61, 0xa0, 0xab, 0x43,
            0xf9, 0x36, 0xa2, 0x4b, 0x00, 0x06, 0x51, 0xd4,
            0xa8, 0x24, 0xfc, 0xdd, 0x57, 0x7f, 0x21, 0x1a,
            0xef, 0x8f, 0x80, 0x6b, 0x16, 0xaf, 0xe8, 0xaf,
        };
        uint8_t m[1000];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x41, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(10, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_11(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #11:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x59, 0xf5, 0xe5, 0x4f, 0xe2, 0x99, 0xc6, 0xa8,
            0x76, 0x4c, 0x6b, 0x19, 0x9e, 0x44, 0x92, 0x4a,
            0x37, 0xf5, 0x9e, 0x2b, 0x56, 0xc3, 0xeb, 0xad,
            0x93, 0x9b, 0x72, 0x89, 0x21, 0x0d, 0xc8, 0xe4,
            0xc2, 0x1b, 0x97, 0x20, 0x16, 0x5b, 0x0f, 0x4d,
            0x43, 0x74, 0xc9, 0x0f, 0x1b, 0xf4, 0xfb, 0x4a,
            0x5a, 0xce, 0x17, 0xa1, 0x16, 0x17, 0x98, 0x01,
            0x50, 0x52, 0x89, 0x3a, 0x48, 0xc3, 0xd1, 0x61,
        };
        uint8_t m[1005];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;

        (void)memset(m, 0x55, sizeof(m));

        (void)tc_sha512_init(&s);
        tc_sha512_update(&s, m, sizeof(m));
        (void)tc_sha512_final(digest, &s);

        result = check_result(11, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_12(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #12:\n");

        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0xce, 0x04, 0x4b, 0xc9, 0xfd, 0x43, 0x26, 0x9d,
            0x5b, 0xbc, 0x94, 0x6c, 0xbe, 0xbc, 0x3b, 0xb7,
            0x11, 0x34, 0x11, 0x15, 0xcc, 0x4a, 0xbd, 0xf2,
            0xed, 0xbc, 0x3f, 0xf2, 0xc5, 0x7a, 0xd4, 0xb1,
            0x5d, 0xeb, 0x69, 0x9b, 0xda, 0x25, 0x7f, 0xea,
            0x5a, 0xef, 0x9c, 0x6e, 0x55, 0xfc, 0xf4, 0xcf,
            0x9d, 0xc2, 0x5a, 0x8c, 0x3c, 0xe2, 0x5f, 0x2e,
            0xfe, 0x90, 0x90, 0x83, 0x79, 0xbf, 0xf7, 0xed,
        };
        uint8_t m[1000];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;
        unsigned int i;

        (void)memset(m, 0x00, sizeof(m));

        (void)tc_sha512_init(&s);
        for (i = 0; i < 1000; ++i) {
                tc_sha512_update(&s, m, sizeof(m));
        }
        (void)tc_sha512_final(digest, &s);

        result = check_result(12, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_13(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #13:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0xda, 0x17, 0x22, 0x79, 0xf3, 0xeb, 0xbd, 0xa9,
            0x5f, 0x6b, 0x6e, 0x1e, 0x5f, 0x0e, 0xbe, 0xc6,
            0x82, 0xc2, 0x5d, 0x3d, 0x93, 0x56, 0x1a, 0x16,
            0x24, 0xc2, 0xfa, 0x90, 0x09, 0xd6, 0x4c, 0x7e,
            0x99, 0x23, 0xf3, 0xb4, 0x6b, 0xca, 0xf1, 0x1d,
            0x39, 0xa5, 0x31, 0xf4, 0x32, 0x97, 0x99, 0x2b,
            0xa4, 0x15, 0x5c, 0x7e, 0x82, 0x7b, 0xd0, 0xf1,
            0xe1, 0x94, 0xae, 0x7e, 0xd6, 0xde, 0x4c, 0xac,
        };
        uint8_t m[32768];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;
        unsigned int i;

        (void)memset(m, 0x5a, sizeof(m));

        (void)tc_sha512_init(&s);
        for (i = 0; i < 16384; ++i) {
                tc_sha512_update(&s, m, sizeof(m));
        }
        (void)tc_sha512_final(digest, &s);

        result = check_result(13, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

unsigned int test_14(void)
{
        unsigned int result = TC_PASS;
        TC_PRINT("SHA512 test #14:\n");
        const uint8_t expected[TC_SHA512_DIGEST_SIZE] = {
            0x14, 0xb1, 0xbe, 0x90, 0x1c, 0xb4, 0x35, 0x49,
            0xb4, 0xd8, 0x31, 0xe6, 0x1e, 0x5f, 0x9d, 0xf1,
            0xc7, 0x91, 0xc8, 0x5b, 0x50, 0xe8, 0x5f, 0x9d,
            0x6b, 0xc6, 0x41, 0x35, 0x80, 0x4a, 0xd4, 0x3c,
            0xe8, 0x40, 0x27, 0x50, 0xed, 0xbe, 0x4e, 0x5c,
            0x0f, 0xc1, 0x70, 0xb9, 0x9c, 0xf7, 0x8b, 0x9f,
            0x4e, 0xcb, 0x9c, 0x7e, 0x02, 0xa1, 0x57, 0x91,
            0x1d, 0x1b, 0xd1, 0x83, 0x2d, 0x76, 0x78, 0x4f,
        };
        uint8_t m[32768];
        uint8_t digest[TC_SHA512_DIGEST_SIZE];
        struct tc_sha512_state_struct s;
        unsigned int i;

        (void)memset(m, 0x00, sizeof(m));

        (void) tc_sha512_init(&s);
        for (i = 0; i < 33280; ++i) {
                tc_sha512_update(&s, m, sizeof(m));
        }
        (void) tc_sha512_final(digest, &s);

        result = check_result(14, expected, sizeof(expected),
                digest, sizeof(digest));
        TC_END_RESULT(result);
        return result;
}

/*
 * Main task to test SHA512
 */

int main(void)
{
        unsigned int result = TC_PASS;
        TC_START("Performing SHA512 tests (NIST tests vectors):");

        result = test_1();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #1 failed.\n");
                goto exitTest;
        }
        result = test_2();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #2 failed.\n");
                goto exitTest;
        }
        result = test_3();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #3 failed.\n");
                goto exitTest;
        }
        result = test_4();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #4 failed.\n");
                goto exitTest;
        }
        result = test_5();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #5 failed.\n");
                goto exitTest;
        }
        result = test_6();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #6 failed.\n");
                goto exitTest;
        }
        result = test_7();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #7 failed.\n");
                goto exitTest;
        }
        result = test_8();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #8 failed.\n");
                goto exitTest;
        }
        result = test_9();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #9 failed.\n");
                goto exitTest;
        }
        result = test_10();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #10 failed.\n");
                goto exitTest;
        }
        result = test_11();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #11 failed.\n");
                goto exitTest;
        }
        result = test_12();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #12 failed.\n");
                goto exitTest;
        }
        /* memory and computation intensive test cases: */
        result = test_13();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #13 failed.\n");
                goto exitTest;
        }
        result = test_14();
        if (result == TC_FAIL) {
                /* terminate test */
                TC_ERROR("SHA512 test #14 failed.\n");
                goto exitTest;
        }

        TC_PRINT("All SHA512 tests succeeded!\n");

exitTest:
        TC_END_RESULT(result);
        TC_END_REPORT(result);
}

