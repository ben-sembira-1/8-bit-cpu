#!/bin/bash
set -euo pipefail
. .env
. scripts_utils.sh

arduino-cli compile -b ${CORE}:${BOARD_NAME} EepromFlasher/EepromFlasher.ino --warnings all 2>&1 | while IFS= read -r line; do
	if echo "$line" | grep -qi "error:"; then
    	red_print "$line"
	elif echo "$line" | grep -qi "warning:"; then
    	yellow_print "$line"
	elif echo "$line" | grep -qi "error during build:"; then
    	red_print "$line"
	else
		echo "$line"
	fi
done

echo
echo "---"
green_print ">>> Successfully compiled the code <<<"
echo "---"

