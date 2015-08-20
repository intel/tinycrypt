################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
# 								           Global Makefile. 
#	  		See lib/Makefile and tests/Makefile for further configuration.
#
################################################################################
include Makefile.conf

all:
	$(MAKE) -C lib
	$(MAKE) -C tests

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C tests clean
	/bin/rm -f *~

