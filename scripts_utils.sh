#!/bin/bash
set -euo pipefail

red_print() {
  printf "\033[31m$1\033[0m\n"
}

green_print() {
  printf "\033[32m$1\033[0m\n"
}

yellow_print() {
  printf "\033[33m$1\033[0m\n"
}
