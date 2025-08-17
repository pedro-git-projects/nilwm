#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"

source "$SCRIPT_DIR/config.sh"
source "$SCRIPT_DIR/lib/log.sh"
source "$SCRIPT_DIR/lib/run_once.sh"
source "$SCRIPT_DIR/lib/x11.sh"

# modules
source "$SCRIPT_DIR/modules/monitors.sh"
source "$SCRIPT_DIR/modules/compositor.sh"
source "$SCRIPT_DIR/modules/wallpaper.sh"
source "$SCRIPT_DIR/modules/services.sh"

require_bins xrandr pgrep feh

log_info "dwm startup: begin"

configure_dual_monitors_horizontal_right   # or set via CONFIG: STARTUP_LAYOUT
restart_or_start_picom
start_services_once
start_daemons
set_wallpapers "${WALLPAPERS[@]}"

log_info "dwm startup: done"
