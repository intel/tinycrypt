#! /bin/bash

set -euo pipefail

VERSION=$(date -Iseconds)
~/sonar/scanner-4.7/bin/sonar-scanner -Dsonar.projectVersion="$VERSION" $*
