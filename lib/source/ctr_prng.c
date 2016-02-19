/* ctr_prng.c - TinyCrypt implementation of CTR-PRNG */

#include <tinycrypt/ctr_prng.h>
#include <tinycrypt/utils.h>
#include <string.h>

//todo comment
static void arrInc(uint8_t arr[], uint32_t len)
{
	uint32_t i;
	if (0 != arr)
	{
		for (i = len; i > 0U; i--)
		{
			if (++arr[i-1] != 0U)
			{
				break;
			}
		}
	}
}

//todo comment
static void tc_ctr_prng_update(TCCtrPrng_t * const ctx, uint8_t const providedData[])
{
	if (0 != ctx)
	{
		/* 10.2.1.2 step 1 */
		uint8_t temp[TC_AES_KEY_SIZE + TC_AES_BLOCK_SIZE];
		uint32_t len = 0U;

		/* 10.2.1.2 step 2 */
		while (len < sizeof temp)
		{
			uint32_t blocklen = sizeof(temp) - len;
			uint8_t output_block[TC_AES_BLOCK_SIZE];

			/* 10.2.1.2 step 2.1 */
			arrInc(ctx->V, sizeof ctx->V);

			/* 10.2.1.2 step 2.2 */
			if (blocklen > TC_AES_BLOCK_SIZE)
			{
				blocklen = TC_AES_BLOCK_SIZE;
			}
			(void)tc_aes_encrypt(output_block, ctx->V, &ctx->key);

			/* 10.2.1.2 step 2.3/step 3 */
			memcpy(&(temp[len]), output_block, blocklen);

			len += blocklen;
		}

		/* 10.2.1.2 step 4 */
		if (0 != providedData)
		{
			uint32_t i;
			for (i = 0U; i < sizeof temp; i++)
			{
				temp[i] ^= providedData[i];
			}
		}

		/* 10.2.1.2 step 5 */
		(void)tc_aes128_set_encrypt_key(&ctx->key, temp);
    
		/* 10.2.1.2 step 6 */
		memcpy(ctx->V, &(temp[TC_AES_KEY_SIZE]), TC_AES_BLOCK_SIZE);
	}
}

int32_t tc_ctr_prng_init(TCCtrPrng_t * const ctx, 
			uint8_t const entropy[], 
			uint32_t entropyLen, 
			uint8_t const personalization[], 
			uint32_t pLen)
{
	int32_t result = TC_FAIL;	
	uint32_t i;
	uint8_t persString[TC_AES_KEY_SIZE + TC_AES_BLOCK_SIZE] = {0U};
	uint8_t seed_material[TC_AES_KEY_SIZE + TC_AES_BLOCK_SIZE];
	uint8_t zeroArr[TC_AES_BLOCK_SIZE] = {0U};
  
	if (0 != personalization)
	{
		/* 10.2.1.3.1 step 1 */
		uint32_t len = pLen;
		if (len > sizeof persString)
		{
			len = sizeof persString;
		}

		/* 10.2.1.3.1 step 2 */
		memcpy(persString, personalization, len);
	}

	if ((0 != ctx) && (0 != entropy) && (entropyLen == sizeof seed_material))
	{
		/* 10.2.1.3.1 step 3 */
		memcpy(seed_material, entropy, sizeof seed_material);
		for (i = 0U; i < sizeof seed_material; i++)
		{
			seed_material[i] ^= persString[i];
		}

		/* 10.2.1.3.1 step 4 */
		(void)tc_aes128_set_encrypt_key(&ctx->key, zeroArr);

		/* 10.2.1.3.1 step 5 */
		memset(ctx->V,   0x00, sizeof ctx->V);
    
		/* 10.2.1.3.1 step 6 */    
		tc_ctr_prng_update(ctx, seed_material);

		/* 10.2.1.3.1 step 7 */
		ctx->reseedCount = 1U;

		result = TC_SUCCESS;
	}
	return result;
}

int32_t tc_ctr_prng_reseed(TCCtrPrng_t * const ctx, 
			uint8_t const entropy[], 
			uint32_t entropyLen)
{
	int32_t result = TC_FAIL;
	
	//todo - add additional input support
	/* 
	 * 10.2.1.4.1 steps 1 - 3 not required - no additional input accepted by 
	 * this reseed function
	 */
	uint32_t seedlen = (uint32_t)TC_AES_KEY_SIZE + (uint32_t)TC_AES_BLOCK_SIZE;
	if ((0 != ctx) && (entropyLen == seedlen))
	{
		/* 10.2.1.4.1 step 4 */
		tc_ctr_prng_update(ctx, entropy);

		/* 10.2.1.4.1 step 5 */
		ctx->reseedCount = 1U;

		result = TC_SUCCESS;
	}
	return result;
}

//todo comment
int32_t tc_ctr_prng_generate(TCCtrPrng_t * const ctx, 
			uint8_t out[], 
			uint32_t outlen)
{
	/* 2^48 - see section 10.2.1 */
	static const uint64_t MAX_REQS_BEFORE_RESEED = 0x1000000000000ULL; 

	/* 2^19 bits - see section 10.2.1 */ 
	static const uint32_t MAX_BYTES_PER_REQ = 65536U; 

	int32_t result = TC_FAIL;

	if ((0 != ctx) && (0 != out) && (outlen < MAX_BYTES_PER_REQ))
	{
		/* 10.2.1.5.1 step 1 */
		if (ctx->reseedCount > MAX_REQS_BEFORE_RESEED)
		{
			result = TC_RESEED_REQ;
		}
		else
		{
			//todo - add additional input support
			/* 10.2.1.5.1 step 2 - no additional input supported, so no action */
      
			/* 10.2.1.5.1 step 3 - implicit */

			/* 10.2.1.5.1 step 4 */
			uint32_t len = 0U;      
			while (len < outlen)
			{
				uint32_t blocklen = outlen - len;
				uint8_t output_block[TC_AES_BLOCK_SIZE];

				/* 10.2.1.5.1 step 4.1 */
				arrInc(ctx->V, sizeof ctx->V);

				/* 10.2.1.5.1 step 4.2 */
				(void)tc_aes_encrypt(output_block, ctx->V, &ctx->key);
      
				/* 10.2.1.5.1 step 4.3/step 5 */
				if (blocklen > TC_AES_BLOCK_SIZE)
				{
					blocklen = TC_AES_BLOCK_SIZE;
				}
				memcpy(&(out[len]), output_block, blocklen);

				len += blocklen;
			}
      
			/* 10.2.1.5.1 step 6 */
			tc_ctr_prng_update(ctx, 0);

			/* 10.2.1.5.1 step 7 */
			ctx->reseedCount++;

			/* 10.2.1.5.1 step 8 */
			result = TC_SUCCESS;
		}
	}

	return result;
}




