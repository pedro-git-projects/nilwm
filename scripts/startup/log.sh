#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

LOG_DIR="${XDG_STATE_HOME:-$HOME/.local/state}/dwm"
mkdir -p "$LOG_DIR"
LOG_FILE="$LOG_DIR/startup.log"

_log() {
  local level="$1"; shift
  # shellcheck disable=SC2145
  printf "[%(%F %T)T] %-5s %s\n" -1 "$level" "$*" | tee -a "$LOG_FILE" >&2
}
log_info()  { _log INFO  "$*"; }
log_warn()  { _log WARN  "$*"; }
log_error() { _log ERROR "$*"; }

set -o pipefail