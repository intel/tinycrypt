################################################################################
#
#      Copyright (C) 2015 by Intel Corporation, All Rights Reserved.
#
#            Global configuration Makefile. Included everywhere.
#
################################################################################

CC=gcc 
CFLAGS = -Os -std=c99 -Wall -Wextra -I../include -I../lib
VPATH = ../include ../lib

export CC
export CFLAGS
export VPATH

################################################################################
