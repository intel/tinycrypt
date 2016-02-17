################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
# 								   Cryptographic Primitives Makefile.
#
################################################################################

include ../config.mk

# Edit the OBJS content to add/remove primitives needed from TinyCrypt library:
OBJS =	utils.o \
	aes_decrypt.o \
	aes_encrypt.o \
	cbc_mode.o \
	ctr_mode.o \
	ccm_mode.o \
	cmac_mode.o \
	hmac.o \
	hmac_prng.o \
	sha256.o \
	ecc.o \
	ecc_dh.o \
	ecc_dsa.o 

all:	$(OBJS)

clean:
	$(RM) *.o *.gch core *dump *~

# Dependencies
aes_decrypt.o:		aes_decrypt.c aes.h utils.o 
aes_encrypt.o:		aes_encrypt.c aes.h utils.o
cbc_mode.o:		cbc_mode.c cbc_mode.h utils.o
ctr_mode.o:	        ctr_mode.c ctr_mode.h utils.o
ccm_mode.o:	        ccm_mode.c ccm_mode.h utils.o
cmac_mode.o:	        ccm_mode.c ccm_mode.h utils.o
hmac.o:		        hmac.c hmac.h utils.o
hmac_prng.o:	        hmac_prng.c hmac_prng.h utils.o
sha256.o:	        sha256.c sha256.h utils.o
ecc_dh.o:		ecc_dh.c ecc_dh.h ecc.o
ecc_dsa.o:		ecc_dsa.c ecc_dsa.h ecc.o
ecc.o:			ecc.c ecc.h
utils.o:		utils.c utils.h

