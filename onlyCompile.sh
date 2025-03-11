#!/bin/bash

set -euo pipefail


BOARD_NAME="-b arduino:avr:mega"
arduino-cli compile $BOARD_NAME EepromFlasher/EepromFlasher.ino --warnings all 2>&1 | while IFS= read -r line; do
	if echo "$line" | grep -qi "error:"; then
    	echo -e "\e[31m$line\e[0m"
	elif echo "$line" | grep -qi "warning:"; then
    	echo -e "\e[33m$line\e[0m"
	elif echo "$line" | grep -qi "error during build:"; then
    	echo -e "\e[31m$line\e[0m"
	else
		echo -e "$line"
	fi
done

echo
echo "---"
echo -e "\e[32m>>> Successfully compiled the code <<<\e[0m"
echo "---"

