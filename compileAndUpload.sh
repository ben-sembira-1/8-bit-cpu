#!/bin/bash
set -euo pipefail
. .env
. scripts_utils.sh

./onlyCompile.sh

arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:mega EepromFlasher/EepromFlasher.ino -v -t
echo -e "\n----\n"
arduino-cli monitor -p /dev/ttyACM0 -c baudrate=9600 | while IFS= read -r line; do
	formatted="$(date +'%H:%M:%S.%3N')\t$line"
	if echo "$line" | grep -qi "Test.*failed\."; then
    	red_print "$formatted"
	elif echo "$line" | grep -qi "Test.*passed\."; then
    	green_print "$formatted"
	else
		echo -e "$formatted"
	fi

done

