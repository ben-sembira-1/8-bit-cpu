#!/bin/bash
set -euo pipefail
. .env

arduino-cli core install ${CORE}
arduino-cli lib install AUnit
