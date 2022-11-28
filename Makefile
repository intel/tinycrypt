################################################################################
#
#      Copyright (C) 2017 by Intel Corporation, All Rights Reserved.
#
# 								           Global Makefile. 
#	  		See lib/Makefile and tests/Makefile for further configuration.
#
################################################################################
include config.mk

all:
	$(MAKE) -C lib
ifeq ($(ENABLE_TESTS),true)
	$(MAKE) -C tests
endif

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C tests clean
	$(MAKE) -f tis.mk clean
	$(RM) *~

report:
	$(MAKE) -f tis.mk report

tis:
	$(MAKE) -f tis.mk tis
