#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"

# shellcheck source=./config.sh
source "$SCRIPT_DIR/config.sh"
# shellcheck source=./lib/log.sh
source "$SCRIPT_DIR/lib/log.sh"
# shellcheck source=./lib/run_once.sh
source "$SCRIPT_DIR/lib/run_once.sh"
# shellcheck source=./lib/x11.sh
source "$SCRIPT_DIR/lib/x11.sh"

# modules
# shellcheck source=./modules/monitors.sh
source "$SCRIPT_DIR/modules/monitors.sh"
# shellcheck source=./modules/compositor.sh
source "$SCRIPT_DIR/modules/compositor.sh"
# shellcheck source=./modules/wallpaper.sh
source "$SCRIPT_DIR/modules/wallpaper.sh"
# shellcheck source=./modules/services.sh
source "$SCRIPT_DIR/modules/services.sh"

require_bins xrandr pgrep feh

log_info "dwm startup: begin"

configure_dual_monitors_horizontal_right   # or set via CONFIG: STARTUP_LAYOUT
restart_or_start_picom
start_services_once
start_daemons
set_wallpapers "${WALLPAPERS[@]}"

log_info "dwm startup: done"
trap - TERM INT EXIT
