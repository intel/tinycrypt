#! /bin/bash

set -euo pipefail

BW_OUT=bw-out

make clean

build-wrapper-linux-x86-64 --out-dir $BW_OUT make
# bear make
# sonar.cfamily.compile-commands=compile_commands.json

VERSION=$(date -Iseconds)

~/sonar/scanner-4.7/bin/sonar-scanner \
   -Dsonar.projectVersion="$VERSION" \
   -Dsonar.cfamily.build-wrapper-output=$BW_OUT \
   $*
