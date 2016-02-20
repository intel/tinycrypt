/*  test_ctr_prng.c - TinyCrypt implementation of some CTR-PRNG tests */

/*
 * Copyright (c) 2016, Chris Morrison
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <test_utils.h>
#include <stdio.h>
#include <stdlib.h>

#include <tinycrypt/ctr_prng.h>

/* utility function to convert hex character representation to their nibble (4 bit) values */
static uint8_t nibbleFromChar(char c)
{
	if(c >= '0' && c <= '9') return c - '0';
	if(c >= 'a' && c <= 'f') return c - 'a' + 10U;
	if(c >= 'A' && c <= 'F') return c - 'A' + 10U;
	return 255U;
}

/* 
 * Convert a string of characters representing a hex buffer into a series of 
 * bytes of that real value 
 */
uint8_t *hexStringToBytes(char *inhex)
{
	uint8_t *retval;
	uint8_t *p;
	int len, i;
	
  len    = strlen(inhex) / 2;
	retval = (uint8_t *)malloc(len+1);
	for(i=0, p = (uint8_t *) inhex; i<len; i++) {
		retval[i] = (nibbleFromChar(*p) << 4) | nibbleFromChar(*(p+1));
		p += 2;
	}
    retval[len] = 0;
	return retval;
}

/*
 * Main task to test CTR PRNG
 */
int main(void)
{
	uint32_t result = TC_PASS;
	uint8_t prngOutput[64];
	TCCtrPrng_t ctx;

	uint8_t * entropy = hexStringToBytes("ce50f33da5d4c1d3d4004eb35244b7f2cd7f2e5076fbf6780a7ff634b249a5fc");

	int32_t ret = tc_ctr_prng_init(&ctx, entropy, 32, 0, 0);
	
	TC_START("Performing CTR-PRNG tests:");

	ret += tc_ctr_prng_generate(&ctx, 0, 0, prngOutput, sizeof prngOutput);
	ret += tc_ctr_prng_generate(&ctx, 0, 0, prngOutput, sizeof prngOutput);

	if (0 == ret)
	{
		result = TC_FAIL;
		goto exitTest;
	}

	{
		uint32_t i;
		for (i = 0U; i < sizeof prngOutput; i++)
		{
			printf(" %02x", prngOutput[i]);
		}
		printf("\n");
	}

 exitTest:
        TC_END_RESULT(result);
        TC_END_REPORT(result);
}

