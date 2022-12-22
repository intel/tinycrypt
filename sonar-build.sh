#! /bin/bash

set -euo pipefail

make clean
build-wrapper-linux-x86-64 --out-dir sonar-build-output make all
