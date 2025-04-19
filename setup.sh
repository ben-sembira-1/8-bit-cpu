#!/bin/bash
set -euo pipefail
. .env

sudo apt-get install -y --no-install-recommends curl ca-certificates
sudo rm -rf /var/lib/apt/lists/*

curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sudo sudo BINDIR=/usr/local/bin sh
arduino-cli version

arduino-cli core install ${CORE}
arduino-cli lib install AUnit
