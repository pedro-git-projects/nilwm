#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

# verify required binaries exist, else fail early
require_bins() {
  local missing=0
  for b in "$@"; do
    command -v "$b" >/dev/null 2>&1 || { log_error "Missing required binary: $b"; missing=1; }
  done
  (( missing == 0 )) || exit 1
}

# run a command iff an identical command line isn’t already running.
run_once() {
  (( "$#" >= 1 )) || { log_error "run_once: no command provided"; return 1; }

  # rebuild as an exact string to compare via pgrep -fa (full cmdline)
  local cmd=( "$@" )
  local needle="${cmd[*]}"

  if pgrep -fa -- "$needle" >/dev/null 2>&1; then
    log_info "run_once: already running: $needle"
    return 0
  fi

  log_info "run_once: starting: $needle"
  nohup "${cmd[@]}" >/dev/null 2>&1 &
  disown
}

# convenience for background commands I may want to duplicate in a single session
bg() {
  nohup "$@" >/dev/null 2>&1 &
  disown
}