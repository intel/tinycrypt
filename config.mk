################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
#            Global configuration Makefile. Included everywhere.
#
################################################################################

CC=gcc 
CFLAGS = -Os -std=c99 -Wall -Wextra -I../lib/include/ -I../lib/source/ -I../tests/include/
VPATH = ../lib/include/tinycrypt/ ../lib/source/

export CC
export CFLAGS
export VPATH

################################################################################
