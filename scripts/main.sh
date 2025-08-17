#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"

echo $SCRIPT_DIR

source_first() {
  for p in "$@"; do
    if [[ -f "$p" ]]; then
      source "$p"
      echo $p
      return 0
    fi
  done
  echo "fatal: none of these files exist: $*" >&2
  exit 1
}

# startup config + logging
source_first \
  "$SCRIPT_DIR/startup/config.sh" \
  "$SCRIPT_DIR/config.sh"

source_first \
  "$SCRIPT_DIR/startup/log.sh" \
  "$SCRIPT_DIR/lib/log.sh"

# libs
source_first "$SCRIPT_DIR/lib/run_once.sh"
source_first "$SCRIPT_DIR/lib/x11.sh"

# modules
source_first "$SCRIPT_DIR/modules/monitors.sh"
source_first "$SCRIPT_DIR/modules/compositor.sh"
source_first "$SCRIPT_DIR/modules/wallpaper.sh"
source_first "$SCRIPT_DIR/modules/services.sh"

require_bins xrandr pgrep feh picom

log_info "dwm startup: begin"

configure_dual_monitors_horizontal_right   # or set via CONFIG: STARTUP_LAYOUT
restart_or_start_picom
start_services_once
start_daemons
set_wallpapers "${WALLPAPERS[@]}"

log_info "dwm startup: done"

