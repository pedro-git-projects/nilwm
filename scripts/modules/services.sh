#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

start_services_once() {
  for entry in "${SERVICES[@]}"; do
    # split string into array safely
    # shellcheck disable=SC2206
    local cmd=( $entry )
    run_once "${cmd[@]}"
  done
}

start_daemons() {
  for app in "${DAEMON_APPS[@]}"; do
    # shellcheck disable=SC2206
    local cmd=( $app )
    log_info "daemon: ${cmd[*]}"
    bg "${cmd[@]}"
  done
}