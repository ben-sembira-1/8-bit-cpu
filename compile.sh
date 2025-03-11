#!/bin/bash

arduino-cli compile -b arduino:avr:mega EepromFlasher/EepromFlasher.ino -v --warnings all
