#!/bin/bash

arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:mega OutputRegisterEepromFlasher/OutputRegisterEepromFlasher.ino -v -t
echo -e "\n----\n"
arduino-cli monitor -p /dev/ttyACM0 -c baudrate=9600 | while IFS= read -r line; do
	formatted="$(date +'%H:%M:%S.%3N')\t$line"
	if echo "$line" | grep -qi "Test.*failed\."; then
    	echo -e "\e[31m$formatted\e[0m"  # Red for lines containing "failed"
	elif echo "$line" | grep -qi "Test.*passed\."; then
    	echo -e "\e[32m$formatted\e[0m"  # Green for other lines
	else
		echo -e "$formatted"
	fi

done

