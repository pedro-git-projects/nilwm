#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

is_connected() {
  local out="$1"
  xrandr --query | grep -qE "^${out} connected"
}