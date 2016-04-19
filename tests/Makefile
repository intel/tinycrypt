################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
# 								           Tests Makefile.
#
################################################################################

include ../config.mk

# Edit the 'all' content to add/remove tests needed from TinyCrypt library:
all:	test_aes \
	test_cbc_mode \
	test_ctr_mode \
	test_cmac_mode \
	test_ccm_mode \
	test_ctr_prng \
	test_hmac \
	test_hmac_prng \
	test_sha256 \
	test_ecc_dh \
	test_ecc_dsa

clean:
	-$(RM) *.o *~
	-$(RM) test_aes
	-$(RM) test_cbc_mode
	-$(RM) test_ctr_mode
	-$(RM) test_ctr_prng
	-$(RM) test_hmac
	-$(RM) test_hmac_prng
	-$(RM) test_sha256
	-$(RM) test_ecc_dh
	-$(RM) test_ecc_dsa
	-$(RM) test_cmac_mode
	-$(RM) test_ccm_mode

# Dependencies
test_aes:	test_aes.o  ../lib/aes_encrypt.o \
		../lib/aes_decrypt.o ../lib/utils.o

test_cbc_mode:	test_cbc_mode.o  ../lib/cbc_mode.o \
		../lib/aes_encrypt.o ../lib/aes_decrypt.o \
		../lib/utils.o 

test_ctr_mode:	test_ctr_mode.o  ../lib/ctr_mode.o \
		../lib/aes_encrypt.o ../lib/utils.o 

test_ctr_prng:	test_ctr_prng.o  ../lib/ctr_prng.o \
		../lib/aes_encrypt.o ../lib/utils.o 

test_cmac_mode:	test_cmac_mode.o  ../lib/aes_encrypt.o ../lib/utils.o \
		../lib/cmac_mode.o

test_ccm_mode:	test_ccm_mode.o  ../lib/aes_encrypt.o \
		../lib/utils.o ../lib/ccm_mode.o

test_hmac:	test_hmac.o  ../lib/hmac.o ../lib/sha256.o \
		../lib/utils.o 

test_hmac_prng:	test_hmac_prng.o ../lib/hmac_prng.o ../lib/hmac.o \
		../lib/sha256.o ../lib/utils.o 

test_sha256:	test_sha256.o  ../lib/sha256.o ../lib/utils.o 

test_ecc_dh:	test_ecc_dh.o ../lib/ecc.o  ../lib/ecc_dh.o test_ecc_utils.o

test_ecc_dsa:	test_ecc_dsa.o ../lib/ecc.o ../lib/utils.o ../lib/ecc_dh.o \
		../lib/ecc_dsa.o ../lib/sha256.o test_ecc_utils.o


# Sub-dependencies
test_aes.o:				aes.h constants.h 
test_cbc_mode.o:			cbc_mode.h constants.h 
test_ctr_mode.o:			ctr_mode.h constants.h 
test_ctr_prng.o:			ctr_prng.h constants.h 
test_cmac_mode.o:			cmac_mode.h aes.h
test_ccm_mode.o:			ccm_mode.h constants.h 
test_hmac.o:				hmac.h sha256.h constants.h 
test_hmac_prng.o:			hmac_prng.h constants.h
test_sha256.o:				sha256.h constants.h 
test_ecc_dh.o:				ecc.h ecc_dh.h constants.h
test_ecc_dsa.o:				ecc.h sha256.h constants.h
test_ecc_utils.o:			ecc.h ecc_dh.h

