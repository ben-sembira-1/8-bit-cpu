#!/bin/bash

arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:mega OutputRegisterEepromFlasher/OutputRegisterEepromFlasher.ino -v -t
echo -e "\n----\n"
cat /dev/ttyACM0 | while IFS= read -r line; do
  echo -e "$(date +'%H:%M:%S.%3N')\t$line"
done

