/* ctr_prng.h - TinyCrypt interface to an CTR-PRNG implementation */

#ifndef __TC_CTR_PRNG_H__
#define __TC_CTR_PRNG_H__

#include <tinycrypt/aes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	/* updated each time another BLOCKLEN_BYTES bytes are produced */
	uint8_t V[TC_AES_BLOCK_SIZE]; 

	/* updated whenever the PRNG is reseeded */
	struct tc_aes_key_sched_struct key;

	/* number of requests since initialisation/reseeding */
	uint64_t reseedCount;
} TCCtrPrng_t;


//todo comment
int32_t tc_ctr_prng_init(TCCtrPrng_t * const ctx, 
			uint8_t const entropy[], 
			uint32_t entropyLen, 
			uint8_t const personalization[], 
			uint32_t pLen);

//todo comment
int32_t tc_ctr_prng_reseed(TCCtrPrng_t * const ctx, 
			uint8_t const entropy[], 
			uint32_t entropyLen);

int32_t tc_ctr_prng_generate(TCCtrPrng_t * const ctx, 
			uint8_t out[], 
			uint32_t outlen);

#ifdef __cplusplus
}
#endif

#endif
