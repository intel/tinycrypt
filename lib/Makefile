################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
# 								   Cryptographic Primitives Makefile.
#
################################################################################

include ../config.mk

# Edit the OBJS content to add/remove primitives needed from TinyCrypt library:
OBJS =	aes_decrypt.o \
	aes_encrypt.o \
	cbc_mode.o \
	ctr_mode.o \
	ctr_prng.o \
	hmac.o \
	hmac_prng.o \
	sha256.o \
	ecc.o \
	ecc_dh.o \
	ecc_dsa.o \
	ccm_mode.o \
	cmac_mode.o \
	utils.o

all:	$(OBJS)

.PHONY: clean

clean:
	-$(RM) *.exe *.o *~

# Dependencies
aes_decrypt.o:		aes.h constants.h utils.h
aes_encrypt.o:		aes.h constants.h utils.h
cbc_mode.o:			cbc_mode.h constants.h utils.h
ctr_mode.o:			ctr_mode.h constants.h utils.h
ctr_prng.o:		    ctr_prng.h constants.h utils.h
ccm_mode.o:			ccm_mode.h constants.h utils.h
cmac_mode.o:		cmac_mode.h aes.h constants.h utils.h
hmac.o:				hmac.h constants.h utils.h
hmac_prng.o:		hmac_prng.h constants.h utils.h
sha256.o:			sha256.h constants.h utils.h
ecc.o:				ecc.h
ecc_dh.o:			ecc_dh.h
ecc_dsa.o:			ecc_dsa.h
utils.o:			utils.h

