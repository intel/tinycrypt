################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
# 								           Tests Makefile.
#
################################################################################

include ../Makefile.conf

# Edit the all content to add/remove tests needed from TinyCrypt library:
all:	test_aes \
	test_cbc_mode \
	test_ctr_mode \
	test_hmac \
	test_hmac_prng \
	test_sha256 


# Dependencies
test_aes:		test_aes.o ../lib/aes_encrypt.o \
						../lib/aes_decrypt.o ../lib/utils.o 

test_cbc_mode:	test_cbc_mode.o ../lib/cbc_mode.o \
						../lib/aes_encrypt.o ../lib/aes_decrypt.o \
						../lib/utils.o 

test_ctr_mode:	test_ctr_mode.o ../lib/ctr_mode.o \
						../lib/aes_encrypt.o ../lib/utils.o 

test_hmac:		test_hmac.o ../lib/hmac.o ../lib/sha256.o \
						../lib/utils.o 

test_hmac_prng:	test_hmac_prng.o ../lib/hmac_prng.o ../lib/hmac.o \
						../lib/sha256.o ../lib/utils.o 

test_sha256:	test_sha256.o ../lib/sha256.o ../lib/utils.o 

# Sub-dependencies
test_aes.o:				test_aes.c ../lib/aes.h
test_cbc_mode.o:	test_cbc_mode.c ../lib/cbc_mode.h ../lib/aes.h
test_ctr_mode.o:	test_ctr_mode.c ../lib/aes.h ../lib/ctr_mode.h
test_hmac.o:			test_hmac.c ../lib/hmac.h ../lib/sha256.h
test_hmac_prng.o:	test_hmac_prng.c ../lib/hmac_prng.h ../lib/utils.h
test_sha256.o:		test_sha256.c ../lib/sha256.h

